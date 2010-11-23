#include <QTextEdit>

#include "editorstack.h"

EditorStack::EditorStack(QWidget *parent) :
    QTabWidget(parent)
{
    visualEditor = new QTextEdit(this);
    addTab(visualEditor, tr("Visual"));
    previewEditor = new QTextEdit(this);
    addTab(previewEditor, tr("Preview"));
    sourceEditor = new QTextEdit(this);
    addTab(sourceEditor, tr("Source"));
    setTabPosition(QTabWidget::South);
}
