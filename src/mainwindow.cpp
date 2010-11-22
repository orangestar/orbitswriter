#include <QAction>
#include <QMenuBar>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    newArtAct = new QAction(tr("&New"), this);

    openArtAct = new QAction(tr("&Open..."), this);

    closeArtAct = new QAction(tr("Close"), this);

    saveArtAct = new QAction(tr("Save"), this);

    saveAsArtAct = new QAction(tr("Save As"), this);

    exitAct = new QAction(tr("E&xit..."), this);

    undoAct = new QAction(tr("Undo"), this);

    redoAct = new QAction(tr("Redo"), this);

    cutAct = new QAction(tr("Cut"), this);

    copyAct = new QAction(tr("Copy"), this);

    pasteAct = new QAction(tr("Paste"), this);

    aboutAct = new QAction(tr("About"), this);
}

void MainWindow::createMenus()
{
    QMenuBar *bar = this->menuBar();

    QMenu *fileMenu = new QMenu(tr("File"), bar);
    fileMenu->addAction(newArtAct);
    fileMenu->addAction(openArtAct);
    fileMenu->addAction(closeArtAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveArtAct);
    fileMenu->addAction(saveAsArtAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
    bar->addMenu(fileMenu);

    QMenu *editMenu = new QMenu(tr("Edit"), bar);
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    bar->addMenu(editMenu);

    QMenu *helpMenu = new QMenu(tr("Help"), bar);
    helpMenu->addAction(aboutAct);
    bar->addMenu(helpMenu);
}
