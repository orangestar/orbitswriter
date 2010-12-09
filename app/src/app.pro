#-------------------------------------------------
#
# OrbitsWriter Application
#
#-------------------------------------------------

QT          += core gui

TARGET       = OrbitsWriter
TEMPLATE     = app


SOURCES     += main.cpp\
               mainwindow.cpp \
               visualeditor.cpp \
    pluginmanager.cpp \
    appcontext.cpp \
    sourceeditor.cpp \
    styleutil.cpp

HEADERS     += mainwindow.h \
               visualeditor.h \
               plugins/textformatinterface.h \
    pluginmanager.h \
    plugins/plugin.h \
    common.h \
    appcontext.h \
    sourceeditor.h \
    styleutil.h

include(qtsingleapplication/qtsingleapplication.pri)

RESOURCES   += ../res/orbitswriter.qrc

win32 {
    RC_FILE += ../res/orbitswriter.rc
}
