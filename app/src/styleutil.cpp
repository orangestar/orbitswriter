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

#include <QTextListFormat>

#include "styleutil.h"

StyleUtil::StyleUtil()
{
}

Style::ListType StyleUtil::isBulletList(const QTextListFormat &format)
{
    switch(format.style()) {
    case QTextListFormat::ListDisc:
    case QTextListFormat::ListCircle:
    case QTextListFormat::ListSquare:
        return Style::BulletList;
    case QTextListFormat::ListDecimal:
    case QTextListFormat::ListLowerAlpha:
    case QTextListFormat::ListLowerRoman:
    case QTextListFormat::ListUpperAlpha:
    case QTextListFormat::ListUpperRoman:
        return Style::NumberedList;
    default:
        return Style::UndefinedListType;
    }
}

QTextListFormat::Style StyleUtil::nextStyle(const QTextListFormat::Style &style)
{
    switch(style) {
    case QTextListFormat::ListDisc:
        return QTextListFormat::ListCircle;
    case QTextListFormat::ListCircle:
        return QTextListFormat::ListSquare;
    case QTextListFormat::ListDecimal:
        return QTextListFormat::ListUpperRoman;
    case QTextListFormat::ListUpperRoman:
        return QTextListFormat::ListUpperAlpha;
    default:
        return QTextListFormat::ListStyleUndefined;
    }
}

QTextListFormat::Style StyleUtil::previousStyle(const QTextListFormat::Style &style)
{
    switch(style) {
    case QTextListFormat::ListSquare:
        return QTextListFormat::ListCircle;
    case QTextListFormat::ListCircle:
        return QTextListFormat::ListDisc;
    case QTextListFormat::ListUpperAlpha:
        return QTextListFormat::ListUpperRoman;
    case QTextListFormat::ListUpperRoman:
        return QTextListFormat::ListDecimal;
    default:
        return QTextListFormat::ListStyleUndefined;
    }
}
