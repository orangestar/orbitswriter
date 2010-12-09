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
   \brief A helper class of styles. All functions in this class is static.
   This class supplies useful functions about text styles.
 */

class StyleUtil
{
public:
    StyleUtil();

    /*!
       \brief True if the \a QTextListFormat is a bullet list, otherwise returns false.
     */
    static Style::ListType isBulletList(const QTextListFormat &format);
};

#endif // STYLEUTIL_H
