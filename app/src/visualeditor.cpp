#include <QDebug>

#include "visualeditor.h"

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

void VisualEditor::setTextFormat(const QString &format)
{
    qDebug() << format;
}
