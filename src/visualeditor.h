#ifndef VISUALEDITOR_H
#define VISUALEDITOR_H

#include <QTextEdit>

class VisualEditor : public QTextEdit
{
    Q_OBJECT
public:
    explicit VisualEditor(QWidget *parent = 0);

signals:

public slots:

};

#endif // VISUALEDITOR_H
