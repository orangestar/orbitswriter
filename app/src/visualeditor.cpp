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

#include <QDebug>
#include <QTextList>
#include <QKeyEvent>
#include <QPalette>

#include "visualeditor.h"
#include "common.h"
#include "appcontext.h"

VisualEditor::VisualEditor(QWidget *parent) :
    QTextEdit(parent)
{
    AppContext *ctx = AppContext::instance();
    setFont(ctx->defaultFont());
    setAlignment(Qt::AlignJustify);
    // FIXME Text background color should be set through blog theme.
//    setTextBackgroundColor(Qt::white);
//    QPalette p = palette();
//    p.setColor(QPalette::Base, QColor(255, 255, 255));
//    setPalette(p);
}

void VisualEditor::applyFormat(const QTextCharFormat &format)
{
    QTextCursor cursor = textCursor();
    if(cursor.hasSelection()) {
        cursor.mergeCharFormat(format);
    }
    this->mergeCurrentCharFormat(format);
}

void VisualEditor::setTextBold(bool value)
{
    QTextCharFormat fmt;
    fmt.setFontWeight(value ? QFont::Bold : QFont::Normal);
    applyFormat(fmt);
}

void VisualEditor::setTextItalic(bool value)
{
    QTextCharFormat fmt;
    fmt.setFontItalic(value);
    applyFormat(fmt);
}

void VisualEditor::setTextStrike(bool value)
{
    QTextCharFormat fmt;
    fmt.setFontStrikeOut(value);
    applyFormat(fmt);
}

void VisualEditor::setTextUnderline(bool value)
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(value);
    applyFormat(fmt);
}

void VisualEditor::fontChanged(const QFont &font)
{
    QTextCharFormat fmt;
    fmt.setFont(font);
    applyFormat(fmt);
}

void VisualEditor::textColorChanged(const QColor &color)
{
    QTextCharFormat fmt;
    fmt.setForeground(color);
    applyFormat(fmt);
}

void VisualEditor::textBackgroundColorChanged(const QColor &color)
{
    QTextCharFormat fmt;
    fmt.setBackground(color);
    applyFormat(fmt);
}

void VisualEditor::textAlignmentChanged(Qt::Alignment align)
{
    this->setAlignment(align);
}

void VisualEditor::insertBulletList(bool insert)
{
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();
    QTextListFormat listFmt;
    if(insert) { // create and insert a new list
        QTextBlockFormat blockFmt = cursor.blockFormat();
        listFmt.setIndent(blockFmt.indent() + 1);
        blockFmt.setIndent(0);
        cursor.setBlockFormat(blockFmt);
        listFmt.setStyle(QTextListFormat::ListDisc);
        cursor.createList(listFmt);
    } else { // remove the exists one
        QTextBlock item = cursor.block();
        cursor.currentList()->remove(item);
        QTextBlockFormat blockFmt = cursor.blockFormat();
        blockFmt.setIndent(0);
        cursor.setBlockFormat(blockFmt);
    }
    cursor.endEditBlock();
}

void VisualEditor::keyPressEvent(QKeyEvent *e)
{
    QTextCursor cursor = this->textCursor();
    QTextList *currList = cursor.currentList();
    if(currList) {
        QTextListFormat listFmt = currList->format();
        switch(e->key()) {
        case Qt::Key_Tab:
            {
                QTextListFormat::Style style = listFmt.style();
                if(style == QTextListFormat::ListDisc) {
                    listFmt.setStyle(QTextListFormat::ListCircle);
                } else if(style == QTextListFormat::ListCircle) {
                    listFmt.setStyle(QTextListFormat::ListSquare);
                }
                listFmt.setIndent(listFmt.indent() + 1);
            }
            break;
        case Qt::Key_Backspace:
//            if(cursor.block().length() == 1) {
//                listFmt.setIndent(listFmt.indent() - 1);
//            } else {
//                QTextEdit::keyPressEvent(e);
//            }
            break;
        default:
            QTextEdit::keyPressEvent(e);
            break;
        }
        currList->setFormat(listFmt);
    } else {
        QTextEdit::keyPressEvent(e);
    }
}
