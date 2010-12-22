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

#include "headingcombobox.h"
#include "common.h"

HeadingItemDelegate::HeadingItemDelegate(QObject *parent /* = 0 */)
    : QStyledItemDelegate(parent)
{
}

void HeadingItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPalette palette = qobject_cast<QComboBox *>(this->parent())->palette();
    QString display = index.model()->data(index).toString();
    QString value = index.model()->data(index, Qt::UserRole).toString();
    painter->save();
    if(option.state.testFlag(QStyle::State_MouseOver)) {
        painter->fillRect(option.rect, palette.highlight());
        painter->setPen(palette.highlightedText().color());
    }
    painter->drawText(option.rect, display + "; " + value);
    painter->restore();
}

HeadingComboBox::HeadingComboBox(QWidget *parent /* = 0 */)
    : QComboBox(parent)
{
    addItem(tr("p"));
    addItem(tr("h1"), Constants::HtmlTag::h1);
    addItem(tr("h2"), Constants::HtmlTag::h2);
    addItem(tr("h3"), Constants::HtmlTag::h3);
    addItem(tr("h4"), Constants::HtmlTag::h4);
    addItem(tr("h5"), Constants::HtmlTag::h5);
    addItem(tr("h6"), Constants::HtmlTag::h6);

    setItemDelegate(new HeadingItemDelegate(this));
}
