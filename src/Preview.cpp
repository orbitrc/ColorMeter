#include "Preview.h"

#include <QPainter>
#include <QDebug>

Preview::Preview(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    setWidth(200);
    setHeight(200);

    QObject::connect(this, &Preview::imageChanged,
                     this, [this]() {
        this->update();
    });
}

QList<QColor> Preview::image() const
{
    return this->m_image;
}

void Preview::setImage(const QList<QColor> &image)
{
    this->m_image = image;

    emit this->imageChanged();
}

void Preview::paint(QPainter *painter)
{
    int i = 0;
    int y = 0;
    while (i < 20 * 20) {
        for (int x = 0; x < 20; ++x) {
            QBrush brush;
            brush.setStyle(Qt::BrushStyle::SolidPattern);
            brush.setColor(this->m_image[i++]);
            painter->setPen(Qt::NoPen);
            if (x == 10 && y == 10) {
                painter->setPen(Qt::red);
            }
            painter->setBrush(brush);
            painter->drawRect(x * 10, y * 10, 10, 10);
        }
        ++y;
    }
}
