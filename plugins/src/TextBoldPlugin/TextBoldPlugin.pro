#-------------------------------------------------
#
# OrbitsWriter Plugin: TextBoldPlugin
#
#-------------------------------------------------

TARGET   = TextBoldPlugin
TEMPLATE = lib

CONFIG  += plugin
CONFIG  += debug

APP_PATH = ../../../app

INCLUDEPATH += $$APP_PATH/src/plugins

HEADERS  = $${INCLUDEPATH}/textformatinterface.h \
           textboldplugin.h
SOURCES  = textboldplugin.cpp

CONFIG(debug, debug|release) {
    DESTDIR  = $$APP_PATH/build/debug/plugins
}

CONFIG(release, debug|release) {
    DESTDIR  = $$APP_PATH/build/release/plugins
}
