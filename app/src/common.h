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

#ifndef COMMON_H
#define COMMON_H

#include <QString>

/*!
   \brief Common constants used in application.
 */
namespace Constants {

    /*!
       \brief List type.
     */
    enum ListType {
        UndefinedListType = -1, /*!< Undefined list type. */
        BulletList = 1,         /*!< Bullet list. */
        NumberedList            /*!< Numbered list. */
    };

    enum Alignment {
        AlignLeft,
        AlignRight,
        AlignCenter,
        AlignJustify
    };

}

#endif // COMMON_H
