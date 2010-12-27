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

   Each QTextBlock will be convert to one HTML tag in order to generate
   the final post. This data stores HTML tag string which should be generated,
   also have the visual text format data that is used for display the tag in
   visual editor and the css data used for HTML generated.

   In order to create an instance, a tag name must be passed as a parameter.
   The tag name should be one of pre-defined strings in namespace HtmlTag.

   You should not use this class as the actual data for text block. Instead,
   each HTML tag have a related class used for this purporse. That is, the actual
   data should be the sub-classes.

   \see QTextBlockUserData
   \see QTextBlock
 */

class HtmlTagData : public QTextBlockUserData
{
public:
    virtual ~HtmlTagData();

    /*!
       \brief HTML tag name.

       The value will be one of items defined in namespace \a HtmlTag.

       \see HtmlTag
     */
    const QString & tagName() const
    {
        return _tagName;
    }

    /*!
       \brief Set visual font which is used for visual editor.

       This will put the font value into \a visualData.

       \param font font value
     */
    void setVisualFont(const QFont & font);

    /*!
       \brief Get visual font which is used for visual editor.
       \param font font value
     */
    QFont visualFont() const;

    const QMap<QString, QVariant> & visualData() const
    {
        return _visualData;
    }

protected:

    /*!
       \brief Constructs an instance of HtmlTagData.
       \param tag tag name to construct
     */
    explicit HtmlTagData(const QString & tag);

    /*!
       \brief Sets visual data.

       Visual data is used for displaying on visual editor. This default impletation
       does nothing. Subclasses should overwrite this function in order to set actual data.
     */
    virtual void setVisualData() {}

    /*!
       \brief Sets CSS data.

       CSS data is used for HTML tag css properties when HTML text generated. This default impletation
       does nothing. Subclasses should overwrite this function in order to set actual data.
     */
    virtual void setCssData() {}

    QString _tagName;
    QMap<QString, QVariant> _visualData;
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

protected:
    virtual void setVisualData();
};

#endif // HTMLTAG_H
