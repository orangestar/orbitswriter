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
        tb = b;
    }

    /*!
       \brief True if text is bold.
       \return true if text is bold, otherwise false
     */
    bool isTextBold() const
    {
        return tb;
    }

    /*!
       \brief Sets true if text is italic, otherwise false.
       \param i true if text is italic
     */
    void setTextItalic(bool i)
    {
        ti = i;
    }

    /*!
       \brief True if text is italic.
       \return true if text is italic, otherwise false
     */
    bool isTextItalic() const
    {
        return ti;
    }

    /*!
       \brief Sets true if text is underlined, otherwise false.
       \param u true if text is underlined
     */
    void setTextUnderline(bool u)
    {
        tu = u;
    }

    /*!
       \brief True if text is underlined.
       \return true if text is underlined, otherwise false
     */
    bool isTextUnderline() const
    {
        return tu;
    }

    /*!
       \brief Sets true if text is strike out, otherwise false.
       \param s true if text is strike out
     */
    void setTextStrikeOut(bool s)
    {
        ts = s;
    }

    /*!
       \brief True if text is strike out.
       \return true if text is strike out, otherwise false
     */
    bool isTextStrikeOut() const
    {
        return ts;
    }

    /*!
       \brief Sets text color.
       \param c text color
     */
    void setTextColor(const QColor &c)
    {
        tc = c;
    }

    /*!
       \brief Gets text color.
       \return current text color
     */
    QColor textColor() const
    {
        return tc;
    }

    /*!
       \brief Sets text background color.
       \param c text background color
     */
    void setTextBackgroundColor(const QColor &c)
    {
        tbc = c;
    }

    /*!
       \brief Gets text background color.
       \return current text background color
     */
    QColor textBackgroundColor() const
    {
        return tbc;
    }

    /*!
       \brief Sets list type.
       \param t list type
     */
    void setListType(Constants::ListType t)
    {
        lt = t;
    }

    /*!
       \brief Gets list type.
       \return current list type
     */
    Constants::ListType listType() const
    {
        return lt;
    }

private:
    bool tb;
    bool ti;
    bool tu;
    bool ts;
    QColor tc;
    QColor tbc;
    Constants::ListType lt;
};

#endif // FORMATDATA_H
