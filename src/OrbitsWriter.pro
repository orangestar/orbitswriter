#-------------------------------------------------
#
# Project OrbitsWriter
#
#-------------------------------------------------

QT       += core gui

TARGET = OrbitsWriter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    visualeditor.cpp

HEADERS  += mainwindow.h \
    visualeditor.h

RESOURCES += \
    ../res/orbitswriter.qrc

win32 {
    RC_FILE += ../res/orbitswriter.rc
}
