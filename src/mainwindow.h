#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QAction *newPostAct;
    QAction *openPostAct;
    QAction *closePostAct;
    QAction *savePostAct;
    QAction *saveAsPostAct;
    QAction *exitAct;

    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;

    QAction *helpAct;
    QAction *aboutAct;

    QAction *publishAct;

    QLabel *msgLabel;

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
};

#endif // MAINWINDOW_H
