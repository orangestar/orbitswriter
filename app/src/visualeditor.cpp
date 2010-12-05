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

#include <QTextList>

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
    setTextBackgroundColor(Qt::white);
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

void VisualEditor::insertList()
{
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();
    QTextListFormat listFmt;
    if(cursor.currentList()) {
        listFmt = cursor.currentList()->format();
    } else {
        QTextBlockFormat blockFmt = cursor.blockFormat();
        listFmt.setIndent(blockFmt.indent() + 1);
        blockFmt.setIndent(0);
        cursor.setBlockFormat(blockFmt);
    }
    listFmt.setStyle(QTextListFormat::ListDisc);
    cursor.createList(listFmt);
    cursor.endEditBlock();
}
