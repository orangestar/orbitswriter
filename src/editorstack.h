#ifndef EDITORSTACK_H
#define EDITORSTACK_H

#include <QTabWidget>

class QTextEdit;

class EditorStack : public QTabWidget
{
    Q_OBJECT
public:
    explicit EditorStack(QWidget *parent = 0);

signals:

public slots:

private:
    QTextEdit *visualEditor;
    QTextEdit *previewEditor;
    QTextEdit *sourceEditor;

};

#endif // EDITORSTACK_H
