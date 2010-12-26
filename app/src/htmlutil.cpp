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

QFont HtmlUtil::getVisualFont(HtmlTag heading)
{
    QFont font;
    switch(heading) {
    case HtmlUtil::h1:
        font.setPointSize(24);
        break;
    case HtmlUtil::h2:
        font.setPointSize(18);
        break;
    case HtmlUtil::h3:
        font.setPointSize(14);
        break;
    case HtmlUtil::h4:
        font.setPointSize(12);
        break;
    case HtmlUtil::h5:
        font.setPointSize(10);
        break;
    case HtmlUtil::h6:
        font.setPointSize(8);
        break;
    case HtmlUtil::p:
        font.setPointSize(AppContext::instance()->defaultFont().pointSize());
        break;
    default:
        // do nothing
        break;
    }
    return font;
}
