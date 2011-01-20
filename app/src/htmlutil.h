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

#ifndef HTMLUTIL_H
#define HTMLUTIL_H

#include "htmltag.h"

class QFont;

namespace orbitswriter
{

/*!
   \class HtmlUtil
   \brief Utilities for html processing.
 */

class HtmlUtil
{
public:

    /*!
       \brief Gets the display font for heading tags.
       \param heading heading tags, valid values are HtmlTag::h1,
       HtmlTag::h2, HtmlTag::h3, HtmlTag::h4, HtmlTag::h5, HtmlTag::h6.
       \return font used for rendering heading tags
     */
    static QFont getHeadingVisualFont(const QString & heading);

private:
    HtmlUtil();
    ~HtmlUtil();
    HtmlUtil(const HtmlUtil &);
    HtmlUtil& operator=(const HtmlUtil &);
}; // end of class HtmlUtil

} // end of namespace orbitswriter

#endif // HTMLUTIL_H
