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

signals:

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
    Q_PROPERTY(bool pickMode READ pickMode WRITE setPickMode NOTIFY pickModeChanged)
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    explicit ColorMeter(QObject *parent = nullptr);
    ~ColorMeter();

    //===========================//
    // Property methods          //
    //===========================//
    QList<QColor> image() const;

    int mouseX() const;
    void setMouseX(int x);

    int mouseY() const;
    void setMouseY(int y);

    bool pickMode() const;
    void setPickMode(bool mode);

    bool running() const;

    QColor color() const;
    void setColor(const QColor& color);

    //==================//
    // Other methods    //
    //==================//
    QPoint centering(int x, int y);
    void capture_image();

    void run();

signals:
    void imageChanged();
    void mouseXChanged(int x);
    void mouseYChanged(int y);
    void pickModeChanged(bool mode);
    void runningChanged(bool running);
    void colorChanged();

    void runLoop();

private:
    QList<QColor> m_image;

    QThread *_thr;
    bool m_running;
    int m_mouseX;
    int m_mouseY;
    bool m_pickMode;
    QColor m_color;
};

#endif // COLORMETER_H
