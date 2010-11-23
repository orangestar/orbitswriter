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
    editorstack.cpp

HEADERS  += mainwindow.h \
    editorstack.h

RESOURCES += \
    ../res/orbitswriter.qrc

win32 {
    RC_FILE += ../res/orbitswriter.rc
}
