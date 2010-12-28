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

#include "visualeditor.h"
#include "appcontext.h"
#include "styleutil.h"
#include "formatdata.h"
#include "htmltag.h"

VisualEditor::VisualEditor(QWidget *parent) :
    QTextEdit(parent)
{
    AppContext *ctx = AppContext::instance();
    setFont(ctx->defaultFont());
    setAlignment(Qt::AlignJustify);
    document()->setModified(false);
    connect(this, SIGNAL(cursorPositionChanged()), SLOT(onCursorPositionChanged()));
    // FIXME Text background color should be set through blog theme.
    setTextBackgroundColor(QColor(255, 255, 255, 0));
}

void VisualEditor::applyFormat(const QTextCharFormat &format)
{
    QTextCursor cursor = textCursor();
    if(cursor.hasSelection()) {
        cursor.mergeCharFormat(format);
    }
    this->mergeCurrentCharFormat(format);
}

void VisualEditor::toggleTextBold(bool value)
{
    QTextCharFormat fmt;
    fmt.setFontWeight(value ? QFont::Bold : QFont::Normal);
    applyFormat(fmt);
}

void VisualEditor::toggleTextItalic(bool value)
{
    QTextCharFormat fmt;
    fmt.setFontItalic(value);
    applyFormat(fmt);
}

void VisualEditor::toggleTextStrike(bool value)
{
    QTextCharFormat fmt;
    fmt.setFontStrikeOut(value);
    applyFormat(fmt);
}

void VisualEditor::toggleTextUnderline(bool value)
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(value);
    applyFormat(fmt);
}

void VisualEditor::changeTextFont(const QFont &font)
{
    QTextCharFormat fmt;
    fmt.setFont(font);
    applyFormat(fmt);
}

void VisualEditor::changeTextColor(const QColor &color)
{
    QTextCharFormat fmt;
    fmt.setForeground(color);
    applyFormat(fmt);
}

void VisualEditor::changeTextBackgroundColor(const QColor &color)
{
    QTextCharFormat fmt;
    fmt.setBackground(color);
    applyFormat(fmt);
}

void VisualEditor::changeTextAlignment(Qt::Alignment align)
{
    this->setAlignment(align);
}

void VisualEditor::insertBulletList(bool insert)
{
    insertList(QTextListFormat::ListDisc, insert);
}

void VisualEditor::insertNumberedList(bool insert)
{
    insertList(QTextListFormat::ListDecimal, insert);
}

void VisualEditor::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();
    if(key == Qt::Key_Tab) {
        // Because there is no TAB in HTML, so we can ignore tab safely.
        // Only when the cursor is in a list, tab is enabled.
        QTextCursor cursor = this->textCursor();
        QTextList *currList = cursor.currentList();
        if(currList) {
            QTextListFormat listFmt = currList->format();
            QTextListFormat::Style style = StyleUtil::nextLevelStyle(listFmt.style());
            if(style != QTextListFormat::ListStyleUndefined) {
                listFmt.setStyle(style);
            }
            listFmt.setIndent(listFmt.indent() + 1);
            cursor.createList(listFmt);
        }
    } else if(key == Qt::Key_Backspace) {
        // When the cursor is in a list and there is no block,
        // backspace will decrease the indent.
        QTextCursor cursor = this->textCursor();
        QTextList *currList = cursor.currentList();
        if(currList) {
            if(cursor.block().length() != 1) {
                // the most common suituation
                QTextEdit::keyPressEvent(e);
            } else {
                // only bullet point left
                QTextListFormat listFmt = currList->format();
                QTextListFormat::Style style = StyleUtil::previousLevelStyle(listFmt.style());
                if(style != QTextListFormat::ListStyleUndefined) {
                    listFmt.setIndent(listFmt.indent() - 1);
                    listFmt.setStyle(style);
                    cursor.createList(listFmt);
                } else {
                    removeListItem(cursor.block());
                    emit listExists(false);
                }
            }
        } else {
            QTextEdit::keyPressEvent(e);
        }
    } else {
        QTextEdit::keyPressEvent(e);
    }
}

void VisualEditor::removeListItem(const QTextBlock &block)
{
    QTextCursor cursor = this->textCursor();
    if(cursor.currentList()) {
        cursor.currentList()->remove(block);
        QTextBlockFormat blockFmt = cursor.blockFormat();
        blockFmt.setIndent(0);
        cursor.setBlockFormat(blockFmt);
    }
}

void VisualEditor::insertList(QTextListFormat::Style style, bool insert)
{
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();
    QTextListFormat listFmt;
    if(insert) { // create and insert a new list
        QTextBlockFormat blockFmt = cursor.blockFormat();
        listFmt.setIndent(blockFmt.indent() + 1);
        blockFmt.setIndent(0);
        cursor.setBlockFormat(blockFmt);
        listFmt.setStyle(style);
        cursor.createList(listFmt);
    } else { // remove the exists item
        removeListItem(cursor.block());
    }
    cursor.endEditBlock();
}

void VisualEditor::onCursorPositionChanged()
{
    QTextCursor cursor = textCursor();
    FormatData fmt;
    // char format
    QTextCharFormat charFmt = cursor.blockCharFormat();
    fmt.setTextBold(charFmt.font().bold());
    fmt.setTextItalic(charFmt.font().italic());
    fmt.setTextStrikeOut(charFmt.font().strikeOut());
    fmt.setTextUnderline(charFmt.font().underline());
    fmt.setTextColor(charFmt.foreground().color());
    fmt.setTextBackgroundColor(charFmt.background().color());
    // non-char format
    if(cursor.currentList()) {
        fmt.setListType(StyleUtil::listType(cursor.currentList()->format()));
    } else {
        fmt.setListType(Constants::UndefinedListType);
    }
    Qt::Alignment align = this->alignment();
    if(align.testFlag(Qt::AlignJustify)) {
        fmt.setAlignment(Constants::AlignJustify);
    } else if(align.testFlag(Qt::AlignLeft)) {
        fmt.setAlignment(Constants::AlignLeft);
    } else if(align.testFlag(Qt::AlignHCenter)) {
        fmt.setAlignment(Constants::AlignCenter);
    } else if(align.testFlag(Qt::AlignRight)) {
        fmt.setAlignment(Constants::AlignRight);
    }
    emit currentFormatChanged(fmt);
}

void VisualEditor::insertHeadingTag(HtmlHeadingTagData *data)
{
    QTextCursor cursor = this->textCursor();
    cursor.beginEditBlock();
    QTextBlockFormat blockFmt;
    blockFmt.setNonBreakableLines(true);
    blockFmt.setPageBreakPolicy(QTextFormat::PageBreak_AlwaysBefore);
    QTextCharFormat charFmt;
    charFmt.setFont(data->visualFont());
    if(cursor.atBlockStart()) {
        cursor.mergeBlockFormat(blockFmt);
        cursor.mergeBlockCharFormat(charFmt);
    } else {
        cursor.insertBlock(blockFmt, charFmt);
    }
    QTextBlock block = cursor.block();
    block.setUserData(data);
    cursor.endEditBlock();
    this->setFocus();
}
