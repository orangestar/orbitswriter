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
    if(format == TextFormat::TEXT_BOLD) {
        textBold(action);
    } else if(format == TextFormat::TEXT_ITALIC) {
        textItalic(action);
    } else if(format == TextFormat::TEXT_STRIKE) {
        textStrike(action);
    } else if(format == TextFormat::TEXT_UNDERLINE) {
        textUnderline(action);
    }
}

void VisualEditor::textBold(QAction *action)
{
    QTextCharFormat fmt;
    fmt.setFontWeight(action->isChecked() ? QFont::Bold : QFont::Normal);
    applyFormat(fmt);
}

void VisualEditor::textItalic(QAction *action)
{

}

void VisualEditor::textStrike(QAction *action)
{

}

void VisualEditor::textUnderline(QAction *action)
{

}
