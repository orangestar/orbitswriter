#-------------------------------------------------
#
# OrbitsWriter Application
#
#-------------------------------------------------

QT += core gui webkit

TARGET = OrbitsWriter
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    appcontext.cpp \
    visualeditor.cpp \
    sourceeditor.cpp \
    pluginmanager.cpp

HEADERS += \
    mainwindow.h \
    appcontext.h \
    visualeditor.h \
    sourceeditor.h \
    pluginmanager.h \
    plugins/plugin.h

include(qtsingleapplication/qtsingleapplication.pri)

RESOURCES   += ../res/orbitswriter.qrc

win32 {
    RC_FILE += ../res/orbitswriter.rc
}
