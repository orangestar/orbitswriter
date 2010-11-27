#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QTabWidget;
class VisualEditor;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void docChanged();

private:
    /*
     * file actions
     */
    QAction *newPostAct;
    QAction *openPostAct;
    QAction *closePostAct;
    QAction *savePostAct;
    QAction *saveAsPostAct;
    QAction *exitAct;

    /*
     * edit actions
     */
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;

    /*
     * help actions
     */
    QAction *helpAct;
    QAction *aboutAct;

    /*
     * format actions
     */
    QAction *textBoldAct;
    QAction *textItalicAct;
    QAction *textUnderlineAct;
    QAction *textStrikeoutAct;
    QAction *textFontAct;
    QAction *olAct;
    QAction *ulAct;
    QAction *tableAct;
    QAction *justifyCenterAct;
    QAction *justifyFillAct;
    QAction *justifyLeftAct;
    QAction *justifyRightAct;

    /*
     * web actions
     */
    QAction *publishAct;

    QTabWidget *editorStack;
    VisualEditor *visualEditor;
    QTextEdit *previewEditor;
    QTextEdit *sourceEditor;

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createEditors();
};

#endif // MAINWINDOW_H
