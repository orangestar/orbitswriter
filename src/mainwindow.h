#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QLabel;
class EditorStack;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    /*
     * file
     */
    QAction *newPostAct;
    QAction *openPostAct;
    QAction *closePostAct;
    QAction *savePostAct;
    QAction *saveAsPostAct;
    QAction *exitAct;

    /*
     * edit
     */
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;

    /*
     * help
     */
    QAction *helpAct;
    QAction *aboutAct;

    /*
     * tool bar
     */
    QAction *publishAct;

    /*
     * format
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

    QLabel *msgLabel;

    EditorStack *editor;

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
};

#endif // MAINWINDOW_H
