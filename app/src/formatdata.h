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

#ifndef FORMATDATA_H
#define FORMATDATA_H

#include <QColor>
#include "common.h"

/*!
   \class FormatData
   \brief A data class used for store format data on current cursor.
 */
class FormatData
{
public:
    FormatData();

    /*!
       \brief Sets true if text is bold, otherwise false.
       \param b true if text is bold
     */
    void setTextBold(bool b)
    {
        _textBold = b;
    }

    /*!
       \brief True if text is bold.
       \return true if text is bold, otherwise false
     */
    bool isTextBold() const
    {
        return _textBold;
    }

    /*!
       \brief Sets true if text is italic, otherwise false.
       \param i true if text is italic
     */
    void setTextItalic(bool i)
    {
        _textItalic = i;
    }

    /*!
       \brief True if text is italic.
       \return true if text is italic, otherwise false
     */
    bool isTextItalic() const
    {
        return _textItalic;
    }

    /*!
       \brief Sets true if text is underlined, otherwise false.
       \param u true if text is underlined
     */
    void setTextUnderline(bool u)
    {
        _textUnderline = u;
    }

    /*!
       \brief True if text is underlined.
       \return true if text is underlined, otherwise false
     */
    bool isTextUnderline() const
    {
        return _textUnderline;
    }

    /*!
       \brief Sets true if text is strike out, otherwise false.
       \param s true if text is strike out
     */
    void setTextStrikeOut(bool s)
    {
        _textStrikeOut = s;
    }

    /*!
       \brief True if text is strike out.
       \return true if text is strike out, otherwise false
     */
    bool isTextStrikeOut() const
    {
        return _textStrikeOut;
    }

    /*!
       \brief Sets text color.
       \param c text color
     */
    void setTextColor(const QColor &c)
    {
        _textColor = c;
    }

    /*!
       \brief Gets text color.
       \return current text color
     */
    QColor textColor() const
    {
        return _textColor;
    }

    /*!
       \brief Sets text background color.
       \param c text background color
     */
    void setTextBackgroundColor(const QColor &c)
    {
        _textBackgroundColor = c;
    }

    /*!
       \brief Gets text background color.
       \return current text background color
     */
    QColor textBackgroundColor() const
    {
        return _textBackgroundColor;
    }

    /*!
       \brief Sets list type.
       \param t list type
     */
    void setListType(Constants::ListType t)
    {
        _listType = t;
    }

    /*!
       \brief Gets list type.
       \return current list type
     */
    Constants::ListType listType() const
    {
        return _listType;
    }

    void setAlignment(Constants::Alignment align)
    {
        _align = align;
    }

    Constants::Alignment alignment() const
    {
        return _align;
    }

private:
    bool _textBold;
    bool _textItalic;
    bool _textUnderline;
    bool _textStrikeOut;
    QColor _textColor;
    QColor _textBackgroundColor;
    Constants::ListType _listType;
    Constants::Alignment _align;
};

#endif // FORMATDATA_H
