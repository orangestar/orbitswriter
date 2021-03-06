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

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QComboBox>
#include <QStyledItemDelegate>

class HtmlHeadingTagData;

/*!
   \class HeadingItemDelegate
   \brief The item renderer for the combo box of heading tags.
 */

class HeadingItemDelegate : public QStyledItemDelegate
{
public:
    HeadingItemDelegate(QObject *parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

/*!
   \class HeadingComboBox
   \brief Combo box of heading tags.
 */

class HeadingComboBox : public QComboBox
{
    Q_OBJECT
public:
    HeadingComboBox(QWidget *parent = 0);

    void showPopup();

signals:

    /*!
       \brief Emits when popup list item selected.
       \param data new heading tag data
     */
    void headingTagSelected(HtmlHeadingTagData *data);

private slots:
    /*!
       \brief Item selected.

       Whether index changes or not, a \a headingTagSelected(HtmlHeadingTagData *)
       will be emitted.
       \param index selected item index
     */
    void itemSelected(int index);
};

#endif // COMPONENTS_H
