#-------------------------------------------------
#
# OrbitsWriter Application
#
#-------------------------------------------------

QT += core gui

TARGET = OrbitsWriter
TEMPLATE = app
DESTDIR = ../build
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/rcc
OBJECTS_DIR = $$DESTDIR/obj

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    appcontext.cpp \
    visualeditor.cpp \
    sourceeditor.cpp \
    styleutil.cpp \
    pluginmanager.cpp \
    formatdata.cpp \
    headingcombobox.cpp \
    htmltag.cpp

HEADERS += \
    common.h \
    mainwindow.h \
    appcontext.h \
    visualeditor.h \
    sourceeditor.h \
    pluginmanager.h \
    styleutil.h \
    plugins/plugin.h \
    formatdata.h \
    headingcombobox.h \
    htmltag.h

include(qtsingleapplication/qtsingleapplication.pri)

RESOURCES   += ../res/orbitswriter.qrc

win32 {
    RC_FILE += ../res/orbitswriter.rc
}
