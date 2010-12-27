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

#ifndef STYLEUTIL_H
#define STYLEUTIL_H

#include "common.h"

class QTextListFormat;

/*!
   \class StyleUtil
   \brief A helper class of styles.

   This class supplies useful functions about text styles.
   All functions in this class are static so there is no need to instance this class.
 */

class StyleUtil
{
public:
    StyleUtil();

    /*!
       \brief Gets the list type.
       \param format current list format
       \return list type of this format
     */
    static Constants::ListType listType(const QTextListFormat &format);

    /*!
       \brief Returns the style of next level item.
       \param style current list style
       \return the style of next level item
     */
    static QTextListFormat::Style nextLevelStyle(const QTextListFormat::Style &style);

    /*!
       \brief Returns the style of previous level item.
       \param style current list style
       \return the style of previous level item
     */
    static QTextListFormat::Style previousLevelStyle(const QTextListFormat::Style &style);

};

#endif // STYLEUTIL_H
