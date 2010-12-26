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

#include <QTextBlockUserData>
#include <QMap>

#include "common.h"

/*!
   \class HtmlTagData
   \brief This is the data for \a QTextBlock.
   <p>Each QTextBlock will be convert to one HTML tag in order to generate
   the final post. This data stores HTML tag string which should be generated,
   also have the visual text format data that is used for display the tag in
   visual editor and the css data used for HTML generated.</p>
   <p>In order to create an instance, a tag name must be passed as a parameter.
   The tag name should be one of pre-defined strings in namespace HtmlTag.</p>
   <p>You should not use this class as the actual data for text block. Instead,
   each HTML tag have a related class used for this purporse. That is, the actual
   data should be the sub-classes.</p>
 */

class HtmlTagData : public QTextBlockUserData
{
public:
    ~HtmlTagData();

    const QString & tagName() const
    {
        return _tagName;
    }

protected:
    explicit HtmlTagData(const QString & tag);

    QString _tagName;
    QMap<QString, QVariant *> _visualData;
    QMap<QString, QString> _cssData;

};

/*!
   \class HtmlHeadingTagData
   \brief HTML heading tag data.
 */

class HtmlHeadingTagData : public HtmlTagData
{
public:
    explicit HtmlHeadingTagData(const QString & tag);
    ~HtmlHeadingTagData();
};

#endif // HTMLTAG_H
