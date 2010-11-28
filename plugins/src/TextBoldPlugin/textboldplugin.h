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

#ifndef TEXTBOLD_H
#define TEXTBOLD_H

#include <QObject>

#include "textformatinterface.h"

/*!
   \class TextBoldPlugin
   \brief Text bold format plugin.
 */

class TextBoldPlugin : public QObject,
                       public TextFormatInterface {
    Q_OBJECT
    Q_INTERFACES(TextFormatInterface)

public:
    QStringList actions() const;
    QTextFormat getTextFormat(const QString &format);
    QString pluginName() const;
    QString pluginId() const;
};

#endif // TEXTBOLDPLUGIN_H
