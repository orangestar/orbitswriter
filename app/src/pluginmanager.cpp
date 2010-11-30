//
// Copyright (C) 2006-2010  by the original authors of Galaxy
// and all its contributors ("Galaxy.org").
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

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
