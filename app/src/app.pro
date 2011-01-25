#-------------------------------------------------
#
# OrbitsWriter Application
#
#-------------------------------------------------

QT += core gui sql

TARGET = OrbitsWriter
TEMPLATE = app
DESTDIR = ../build
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/rcc
OBJECTS_DIR = $$DESTDIR/obj

INCLUDEPATH += ../lib/bdb/include

LIBS += ../lib/bdb/libdb_cxx.a

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
    htmlutil.cpp \
    htmltag.cpp \
    blogprofileconfigwizard.cpp \
    profilemanager.cpp \
    berkeleydbworker.cpp

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
    htmlutil.h \
    htmltag.h \
    blogprofileconfigwizard.h \
    profilemanager.h \
    berkeleydbworker.h \
    dbworker.h

include(qtsingleapplication/qtsingleapplication.pri)

RESOURCES += ../res/orbitswriter.qrc

win32 {
    RC_FILE += ../res/orbitswriter.rc
}
