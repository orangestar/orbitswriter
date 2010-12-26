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
#include "htmlutil.h"

HeadingItemDelegate::HeadingItemDelegate(QObject *parent /* = 0 */)
    : QStyledItemDelegate(parent)
{
}

void HeadingItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPalette palette = qobject_cast<QComboBox *>(this->parent())->palette();
    const QAbstractItemModel *model = index.model();
    QString display = model->data(index, Qt::DisplayRole).toString();
    painter->save();
    if(option.state.testFlag(QStyle::State_MouseOver)) {
        painter->fillRect(option.rect, palette.highlight());
        painter->setPen(palette.highlightedText().color());
    }
    painter->setFont(HtmlUtil::getVisualFont((HtmlUtil::HtmlTag)model->data(index, Qt::UserRole).toInt()));
    painter->drawText(option.rect, display);
    painter->restore();
}

QSize HeadingItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    QSize size;
    QFontMetrics m(HtmlUtil::getVisualFont((HtmlUtil::HtmlTag)index.model()->data(index, Qt::UserRole).toInt()));
    size.setWidth(m.width(index.model()->data(index).toString()));
    size.setHeight(m.height() + 10);
    return size;
}

HeadingComboBox::HeadingComboBox(QWidget *parent /* = 0 */)
    : QComboBox(parent)
{
    addItem(tr("paragraph"), HtmlUtil::p);
    addItem(tr("Heading 1"), HtmlUtil::h1);
    addItem(tr("Heading 2"), HtmlUtil::h2);
    addItem(tr("Heading 3"), HtmlUtil::h3);
    addItem(tr("Heading 4"), HtmlUtil::h4);
    addItem(tr("Heading 5"), HtmlUtil::h5);
    addItem(tr("Heading 6"), HtmlUtil::h6);

    setItemDelegate(new HeadingItemDelegate(this));
}

void HeadingComboBox::showPopup()
{
    view()->setFixedWidth(180);
    QComboBox::showPopup();
}
