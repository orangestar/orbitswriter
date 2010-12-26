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

class QFont;

class HtmlUtil
{
public:

    enum HtmlTag {
        h1,
        h2,
        h3,
        h4,
        h5,
        h6,
        p
    };

    /*!
       \brief Gets the display font for heading tags.
       \param heading heading tags, valid values are HtmlUtil::h1,
       HtmlUtil::h2, HtmlUtil::h3, HtmlUtil::h4, HtmlUtil::h5, HtmlUtil::h6.
       \return font used for rendering heading tags
     */
    static QFont getVisualFont(HtmlTag heading);

private:
    HtmlUtil();
    ~HtmlUtil();
    HtmlUtil(const HtmlUtil &);
    HtmlUtil& operator=(const HtmlUtil &);
};

#endif // HTMLUTIL_H
