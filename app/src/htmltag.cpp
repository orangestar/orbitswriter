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

#include "htmltag.h"
#include "htmlutil.h"

////////////////////////////////////////////////////////////////////////////////
//
// HtmlTagData
//
////////////////////////////////////////////////////////////////////////////////

HtmlTagData::HtmlTagData(const QString & tag)
    : _tagName(tag)
{
    setVisualData();
    setCssData();
}

HtmlTagData::~HtmlTagData()
{
}

void HtmlTagData::setVisualFont(const QFont &font)
{
    _visualData.insert(VisualFormat::font, QVariant(font));
}

QFont HtmlTagData::visualFont() const
{
    return _visualData.value(VisualFormat::font).value<QFont>();
}

////////////////////////////////////////////////////////////////////////////////
//
// HtmlHeadingTagData
//
////////////////////////////////////////////////////////////////////////////////

HtmlHeadingTagData::HtmlHeadingTagData(const QString &tag)
    : HtmlTagData(tag)
{
    setVisualData();
}

HtmlHeadingTagData::~HtmlHeadingTagData()
{
}

void HtmlHeadingTagData::setVisualData()
{
    setVisualFont(HtmlUtil::getVisualFont(_tagName));
}
