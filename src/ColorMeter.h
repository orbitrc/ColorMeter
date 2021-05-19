#ifndef COLORMETER_H
#define COLORMETER_H

#include <QObject>
#include <QColor>
#include <QThread>

class ColorMeter;

class MoveEventWorker : public QObject
{
    Q_OBJECT
public:
    void setColorMeter(ColorMeter *colorMeter)
    {
        this->_colorMeter = colorMeter;
    }

public slots:
    void doWork();

private:
    ColorMeter *_colorMeter;
};

class ColorMeter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QColor> image READ image NOTIFY imageChanged)
    Q_PROPERTY(int mouseX READ mouseX WRITE setMouseX NOTIFY mouseXChanged)
    Q_PROPERTY(int mouseY READ mouseY WRITE setMouseY NOTIFY mouseYChanged)
public:
    explicit ColorMeter(QObject *parent = nullptr);
    ~ColorMeter();

    QList<QColor> image() const;

    int mouseX() const;
    void setMouseX(int x);

    int mouseY() const;
    void setMouseY(int y);

    void capture_image();

    void run();

signals:
    void imageChanged();
    void mouseXChanged(int x);
    void mouseYChanged(int y);

    void runLoop();

private:
    QList<QColor> m_image;

    QThread *_thr;
    bool _running;
    int m_mouseX;
    int m_mouseY;
};

#endif // COLORMETER_H
