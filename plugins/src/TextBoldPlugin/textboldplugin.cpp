#include <QStringList>
#include <QTextFormat>
#include <QTextCharFormat>
#include <QFont>
#include <QtPlugin>

#include "textboldplugin.h"

QString TextBoldPlugin::pluginId() const
{
    return "TextBoldPlugin";
}

QString TextBoldPlugin::pluginName() const
{
    return QString("TextBold");
}

QStringList TextBoldPlugin::actions() const
{
    return QStringList() << "Bold";
}

QTextFormat TextBoldPlugin::getTextFormat(const QString &format)
{
    QTextCharFormat fmt;
    fmt.setFontWeight(QFont::Bold);
    return fmt;
}

Q_EXPORT_PLUGIN2(TextBoldPlugin, TextBoldPlugin)
