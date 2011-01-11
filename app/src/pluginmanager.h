//
// Copyright (C) 2006-2010  by the original authors of Galaxy
// and all its contributors ("Galaxy.org").
//
// This file is part of OrbitsWriter.
//
// OrbitsWriter is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OrbitsWriter is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with OrbitsWriter.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QList>
#include <QMap>

namespace orbitswriter
{

namespace plugin
{
class Plugin;
}

/*!
   \class PluginManager
   \brief Plugin manager.

   This is a singleton manager class. Gets instance using PluginManager::instance().
 */

class PluginManager
{
public:
    /*!
       \brief Gets the only instance of \a PluginManager.
       \return pointer to the instance
     */
    static inline PluginManager * instance()
    {
        static PluginManager mgr;
        return &mgr;
    }

    /*!
       \brief Loads plugins.
     */
    void loadPlugins();

private:
    PluginManager() { }
    ~PluginManager() { }
    PluginManager(const PluginManager &);
    PluginManager& operator=(const PluginManager &);
}; // end of class PluginManager

} // end of namespace orbitswriter

#endif // PLUGINMANAGER_H
