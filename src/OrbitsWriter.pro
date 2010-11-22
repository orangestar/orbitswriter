#-------------------------------------------------
#
# Project OrbitsWriter
#
#-------------------------------------------------

QT       += core gui

TARGET = OrbitsWriter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

RESOURCES += \
    ../res/orbitswriter.qrc

win32 {
    RC_FILE += ../res/orbitswriter.rc
}
