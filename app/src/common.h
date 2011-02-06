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
#include <QObject>

namespace orbitswriter
{

/*!
   \brief Common constants used in application.
 */
namespace Constants
{

    /*!
       \brief List type.
     */
    enum ListType {
        UndefinedListType = -1, /*!< Undefined list type. */
        BulletList = 1,         /*!< Bullet list. */
        NumberedList            /*!< Numbered list. */
    };

    /*!
       \brief Alignment.
     */
    enum Alignment {
        AlignLeft,     /*!< Alignment left. */
        AlignRight,    /*!< Alignment right. */
        AlignCenter,   /*!< Alignment center. */
        AlignJustify   /*!< Alignment justify. */
    };

    const QString DefaultFlagString = QObject::tr(" (Default)");

} // end of namespace Constants

/*!
   \brief Html tags used in application.
 */
namespace HtmlTag
{
    /*!
       \brief Heading 1(&lt;h1 /&gt;).
     */
    const QString h1 = QString("h1");

    /*!
       \brief Heading 2(&lt;h2 /&gt;).
     */
    const QString h2 = QString("h2");

    /*!
       \brief Heading 3(&lt;h3 /&gt;).
     */
    const QString h3 = QString("h3");

    /*!
       \brief Heading 4(&lt;h4 /&gt;).
     */
    const QString h4 = QString("h4");

    /*!
       \brief Heading 5(&lt;h5 /&gt;).
     */
    const QString h5 = QString("h5");

    /*!
       \brief Heading 6(&lt;h6 /&gt;).
     */
    const QString h6 = QString("h6");

    /*!
       \brief Paragraph(&lt;p /&gt;).
     */
    const QString p = QString("p");
} // end of namespace HtmlTag

/*!
   \brief CSS names used in application.
 */
namespace Css
{

} // end of namespace Css

/*!
   \brief Visual format used for displaying on visual editor.
 */
namespace VisualFormat
{
    const QString font = QString("font");
} // end of namespace VisualFormat

} // end of namespace orbitswriter

#endif // COMMON_H
