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

#ifndef HTMLTAG_H
#define HTMLTAG_H

class QString;
class QFont;

/*!
   \class HtmlTag
   \brief Tags that the application can process.
 */

class HtmlTag
{
public:
    HtmlTag();

    /*!
       \brief HTML tag <h1 />.
     */
    static const QString h1;

    /*!
       \brief HTML tag <h2 />.
     */
    static const QString h2;

    /*!
       \brief HTML tag <h3 />.
     */
    static const QString h3;

    /*!
       \brief HTML tag <h4 />.
     */
    static const QString h4;

    /*!
       \brief HTML tag <h5 />.
     */
    static const QString h5;

    /*!
       \brief HTML tag <h6 />.
     */
    static const QString h6;

    /*!
       \brief Gets the display font for heading tags.
       \param heading heading tags, valid values are HtmlTag::h1,
       HtmlTag::h2, HtmlTag::h3, HtmlTag::h4, HtmlTag::h5, HtmlTag::h6.
       \return font used for rendering heading tags
     */
    static QFont getVisualFont(const QString & heading);
};

#endif // HTMLTAG_H
