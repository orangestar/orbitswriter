#include <QAction>

#include "visualeditor.h"
#include "common.h"

VisualEditor::VisualEditor(QWidget *parent) :
    QTextEdit(parent)
{
}

void VisualEditor::applyFormat(const QTextCharFormat &format)
{
    QTextCursor cursor = textCursor();
    if(cursor.hasSelection()) {
        cursor.mergeCharFormat(format);
    }
    this->mergeCurrentCharFormat(format);
}

void VisualEditor::setTextFormat(QObject* a)
{
    QAction *action = qobject_cast<QAction*>(a);
    QString format = action->data().toString();
    bool val = action->isChecked();
    if(format == TextFormat::TEXT_BOLD) {
        setTextBold(val);
    } else if(format == TextFormat::TEXT_ITALIC) {
        setTextItalic(val);
    } else if(format == TextFormat::TEXT_STRIKE) {
        setTextStrike(val);
    } else if(format == TextFormat::TEXT_UNDERLINE) {
        setTextUnderline(val);
    }
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
