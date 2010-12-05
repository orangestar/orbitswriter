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

#ifndef PLUGIN_H
#define PLUGIN_H

class QString;
class QStringList;

/*!
   \interface Plugin
   \brief Common plugin interface
   All plugin interfaces should extends this one.
 */

class Plugin
{
public:

    /*!
       \brief Gets plugin id.
       Plugin id is used for identifying the plugin inside application.
     */
    virtual QString pluginId() const = 0;

    /*!
       \brief Gets plugin name.
       Plugin name is the name of this plugin. This name will be added into
       plugin management list. It should be a human-readable string.
     */
    virtual QString pluginName() const = 0;

    /*!
       \brief Actions ids.
       Ids are used for identifying different actions.
       More than one action can be added into one plugin.
     */
    virtual QStringList actions() const = 0;
};

#endif // PLUGIN_H
