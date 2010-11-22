#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QAction *newArtAct;
    QAction *openArtAct;
    QAction *closeArtAct;
    QAction *saveArtAct;
    QAction *saveAsArtAct;
    QAction *exitAct;

    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;

    QAction *aboutAct;

    void createActions();
    void createMenus();
};

#endif // MAINWINDOW_H
