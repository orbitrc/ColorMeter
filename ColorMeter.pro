QT += quick widgets

CONFIG += c++11

LIBS += -lX11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/ColorMeter.cpp \
        src/Preview.cpp \
        src/main.cpp

HEADERS += \
        src/ColorMeter.h \
        src/Preview.h

RESOURCES += resources/resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = /usr/lib/blusher/qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

DEFINES += BLUSHER_APP_VERSION=\\\"0.1.0\\\" \
        "BLUSHER_APP_NAME=\"\\\"Color Meter\\\"\"" \
        BLUSHER_DEBUG

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

