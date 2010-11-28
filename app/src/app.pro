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
    pluginmanager.cpp

HEADERS     += mainwindow.h \
               visualeditor.h \
               plugins\textformatinterface.h \
    pluginmanager.h \
    plugins/plugin.h

RESOURCES   += ../res/orbitswriter.qrc

win32 {
    RC_FILE += ../res/orbitswriter.rc
}
