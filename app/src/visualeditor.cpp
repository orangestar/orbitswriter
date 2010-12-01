//
// Copyright (C) 2006-2010  by the original authors of Galaxy
// and all its contributors ("Galaxy.org").
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include <QAction>

#include "visualeditor.h"
#include "common.h"
#include "appcontext.h"

VisualEditor::VisualEditor(QWidget *parent) :
    QTextEdit(parent)
{
    AppContext *ctx = AppContext::instance();
    setFont(ctx->defaultFont());
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
