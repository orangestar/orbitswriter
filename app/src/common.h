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
   \namespace TextFormat
   \brief Text format.
 */
namespace TextFormat
{
    /*!
       \brief Text bold.
     */
    const QString TEXT_BOLD("TextBold");

    /*!
       \brief Text italic.
     */
    const QString TEXT_ITALIC("TextItalic");

    /*!
       \brief Text underline.
     */
    const QString TEXT_UNDERLINE("TextUnderline");

    /*!
       \brief Text strike.
     */
    const QString TEXT_STRIKE("TextStrike");

}

namespace AppContextValue
{
    const QString DEFAULT_FONT("defaultFont");
}

#endif // COMMON_H
