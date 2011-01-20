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

#include <QtGui>

#include "htmlutil.h"
#include "appcontext.h"

using namespace orbitswriter;

QFont HtmlUtil::getHeadingVisualFont(const QString & heading)
{
    QFont font = AppContext::instance()->defaultFont();
    if(heading == HtmlTag::h1) {
        font.setPointSize(24);
        font.setWeight(QFont::Bold);
    } else if(heading == HtmlTag::h2) {
        font.setPointSize(18);
        font.setWeight(QFont::Bold);
    } else if(heading == HtmlTag::h3) {
        font.setPointSize(14);
        font.setWeight(QFont::Bold);
    } else if(heading == HtmlTag::h4) {
        font.setPointSize(12);
        font.setWeight(QFont::Bold);
    } else if(heading == HtmlTag::h5) {
        font.setPointSize(10);
        font.setWeight(QFont::Bold);
    } else if(heading == HtmlTag::h6) {
        font.setPointSize(8);
        font.setWeight(QFont::Bold);
    } else if(heading == HtmlTag::p) {
        // use default font
    }
    return font;
}
