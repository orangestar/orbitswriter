#include <QApplication>
#include <QDir>
#include <QPluginLoader>

#include "pluginmanager.h"
#include "plugins/textformatinterface.h"

void PluginManager::loadPlugins()
{
    QDir pluginsDir(QApplication::applicationDirPath() + "/plugins");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        if(TextFormatInterface *plugin = qobject_cast<TextFormatInterface *>(loader.instance())) {
            _formatPluginList.append(plugin);
            _pluginRegTable.insert(plugin->pluginId(), plugin);
        }
    }
}
