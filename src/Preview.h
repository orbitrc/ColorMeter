#ifndef PREVIEW_H
#define PREVIEW_H

#include <QQuickPaintedItem>

class Preview : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QList<QColor> image READ image WRITE setImage NOTIFY imageChanged)
public:
    Preview(QQuickItem *parent = nullptr);

    QList<QColor> image() const;
    void setImage(const QList<QColor>& image);

    virtual void paint(QPainter *painter);

signals:
    void imageChanged();

private:
    QList<QColor> m_image;

};

#endif // PREVIEW_H
