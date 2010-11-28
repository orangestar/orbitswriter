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

#ifndef TEXTFORMATINTERFACE_H
#define TEXTFORMATINTERFACE_H

#include "plugin.h"

class QTextFormat;

/*!
   \interface TextFormatInterface
   \brief Text format plugin interface
   Interface for text formats, such as bold, italic and so on.
 */

class TextFormatInterface : public Plugin
{
public:
    virtual ~TextFormatInterface() { }

    /*!
       \brief Gets text format.
       Gets text format by format id. This id must be one item in
       the list that TextFormatInterface::formats() returns.
     */
    virtual QTextFormat getTextFormat(const QString &format) = 0;
};

Q_DECLARE_INTERFACE(TextFormatInterface,
                    "org.galaxy.OrbitsWriter.TextFormatInterface/1.0")

#endif // TEXTFORMATINTERFACE_H
