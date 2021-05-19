#include "ColorMeter.h"

#include <QDebug>
#include <QPoint>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

void MoveEventWorker::doWork()
{
    Display *dpy;
    XEvent evt;

    dpy = XOpenDisplay(NULL);

    XAllowEvents(dpy, AsyncBoth, CurrentTime);
    XGrabPointer(dpy,
        DefaultRootWindow(dpy),
        1,
        PointerMotionMask | ButtonPressMask,
        GrabModeAsync,
        GrabModeAsync,
        None,
        None,
        CurrentTime);

//        this->_running = true;
//        while (this->_running) {
    while (this->_colorMeter->running()) {
        XNextEvent(dpy, &evt);
        switch (evt.type) {
        case MotionNotify:
//            qDebug() << evt.xmotion.x_root;
            this->_colorMeter->setMouseX(evt.xmotion.x_root);
            this->_colorMeter->setMouseY(evt.xmotion.y_root);
            break;
        case ButtonPress:
            this->_colorMeter->setMouseX(evt.xmotion.x_root);
            this->_colorMeter->setMouseY(evt.xmotion.y_root);
            this->_colorMeter->setPickMode(false);
            XUngrabPointer(dpy, CurrentTime);
            break;
        default:
            break;
        }
    }
    XCloseDisplay(dpy);
}


ColorMeter::ColorMeter(QObject *parent)
    : QObject(parent)
{
    this->m_mouseX = 0;
    this->m_mouseY = 0;
    this->m_pickMode = false;

    this->capture_image();
    QObject::connect(this, &ColorMeter::mouseXChanged,
                     this, [this]() {
        if (this->m_pickMode) {
            this->capture_image();
        }
    });
    QObject::connect(this, &ColorMeter::mouseYChanged,
                     this, [this]() {
        if (this->m_pickMode) {
            this->capture_image();
        }
    });

    this->m_running = false;

    QObject::connect(this, &ColorMeter::pickModeChanged,
                     this, [this](bool mode) {
        if (mode) {
            this->m_running = true;
            this->run();
        } else {
            this->m_running = false;
        }
    });
}

ColorMeter::~ColorMeter()
{
    this->_thr->quit();
    this->_thr->wait();
}

QList<QColor> ColorMeter::image() const
{
    return this->m_image;
}

int ColorMeter::mouseX() const
{
    return this->m_mouseX;
}

void ColorMeter::setMouseX(int x)
{
    if (this->m_mouseX != x) {
        this->m_mouseX = x;

        emit this->mouseXChanged(x);
    }
}

int ColorMeter::mouseY() const
{
    return this->m_mouseY;
}

void ColorMeter::setMouseY(int y)
{
    if (this->m_mouseY != y) {
        this->m_mouseY = y;

        emit this->mouseYChanged(y);
    }
}

bool ColorMeter::pickMode() const
{
    return this->m_pickMode;
}

void ColorMeter::setPickMode(bool mode)
{
    if (this->m_pickMode != mode) {
        this->m_pickMode = mode;

        emit this->pickModeChanged(mode);
    }
}

bool ColorMeter::running() const
{
    return this->m_running;
}

QColor ColorMeter::color() const
{
    return this->m_color;
}

void ColorMeter::setColor(const QColor &color)
{
    if (this->m_color != color) {
        this->m_color = color;

        emit this->colorChanged();
    }
}

QPoint ColorMeter::centering(int x, int y)
{
    x = x - 10;
    y = y - 10;

    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }

    QPoint p(x, y);
    return p;
}

void ColorMeter::capture_image()
{
    Display *dpy;
    XImage *img;

    QPoint centered = this->centering(this->mouseX(), this->mouseY());
    dpy = XOpenDisplay(NULL);
    img = XGetImage(dpy, XDefaultRootWindow(dpy),
        centered.x(), centered.y(),
        20, 20,
        AllPlanes, ZPixmap);

    int i = 0;
    int x = 0;
    int y = 0;
    XColor color;
    this->m_image.clear();
    while (i < 20 * 20) {
        color.pixel = XGetPixel(img, x, y);

        XQueryColor(dpy,
            XDefaultColormap(dpy, XDefaultScreen(dpy)),
            &color);

        this->m_image.append(QColor::fromRgb(
            color.red / 256,
            color.green / 256,
            color.blue / 256));

        if (i != 0 && i % 20 == 0) {
            x = 0;
            ++y;
        }
        // Colour of centre.
        if (x == 10 && y == 10) {
            this->setColor(QColor::fromRgb(
                color.red / 256,
                color.green / 256,
                color.blue / 256));
        }
        ++x;
        ++i;
    }
    emit this->imageChanged();
    XDestroyImage(img);
    XCloseDisplay(dpy);
}

void ColorMeter::run()
{
    MoveEventWorker *worker = new MoveEventWorker;
    worker->setColorMeter(this);
    this->_thr = new QThread;
    worker->moveToThread(this->_thr);
    QObject::connect(this->_thr, &QThread::finished,
                     worker, &MoveEventWorker::deleteLater);
    QObject::connect(this, &ColorMeter::runLoop,
                     worker, &MoveEventWorker::doWork);

    this->_thr->start();
    emit this->runLoop();
}
