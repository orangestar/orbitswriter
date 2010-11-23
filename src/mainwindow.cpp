#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QLabel>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    docArea = new QTextEdit(this);

    this->setWindowIcon(QIcon(":/img/orbitswriter"));
    this->setCentralWidget(docArea);
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    newPostAct = new QAction(QIcon(":/img/new_16"), tr("&New"), this);
    newPostAct->setShortcut(QKeySequence::New);
    newPostAct->setStatusTip(tr("Create a new post."));

    openPostAct = new QAction(QIcon(":/img/open_16"), tr("&Open..."), this);
    openPostAct->setShortcut(QKeySequence::Open);
    openPostAct->setStatusTip(tr("Open a post."));

    closePostAct = new QAction(QIcon(":/img/close_16"), tr("Close"), this);
    closePostAct->setShortcut(QKeySequence::Close);
    closePostAct->setStatusTip(tr("Close the post."));

    savePostAct = new QAction(QIcon(":/img/save_16"), tr("Save"), this);
    savePostAct->setShortcut(QKeySequence::Save);
    savePostAct->setStatusTip(tr("Save the post."));

    saveAsPostAct = new QAction(QIcon(":/img/save_as_16"), tr("Save As"), this);
    saveAsPostAct->setShortcut(QKeySequence::SaveAs);
    saveAsPostAct->setStatusTip(tr("Save the post as another one."));

    exitAct = new QAction(QIcon(":/img/exit_16"), tr("E&xit..."), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit OrbitsWriter."));

    undoAct = new QAction(QIcon(":/img/undo_16"), tr("Undo"), this);
    undoAct->setShortcut(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo."));

    redoAct = new QAction(QIcon(":/img/redo_16"), tr("Redo"), this);
    redoAct->setShortcut(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo."));

    cutAct = new QAction(QIcon(":/img/cut_16"), tr("Cut"), this);
    cutAct->setShortcut(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut."));

    copyAct = new QAction(QIcon(":/img/copy_16"), tr("Copy"), this);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy."));

    pasteAct = new QAction(QIcon(":/img/paste_16"), tr("Paste"), this);
    pasteAct->setShortcut(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste."));

    helpAct = new QAction(QIcon(":/img/help_16"), tr("Help"), this);
    helpAct->setShortcut(QKeySequence::HelpContents);
    helpAct->setStatusTip(tr("Open help contents."));

    aboutAct = new QAction(QIcon(":/img/about_16"), tr("About"), this);
    aboutAct->setStatusTip(tr("About OrbitsWriter."));

    publishAct = new QAction(QIcon(":/img/publish_32"), tr("Publish"), this);
    publishAct->setStatusTip(tr("Publish the post."));
}

void MainWindow::createMenus()
{
    QMenuBar *bar = this->menuBar();

    QMenu *fileMenu = new QMenu(tr("File"), bar);
    fileMenu->addAction(newPostAct);
    fileMenu->addAction(openPostAct);
    fileMenu->addAction(closePostAct);
    fileMenu->addSeparator();
    fileMenu->addAction(savePostAct);
    fileMenu->addAction(saveAsPostAct);
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
    helpMenu->addAction(helpAct);
    helpMenu->addAction(aboutAct);
    bar->addMenu(helpMenu);
}

void MainWindow::createToolBars()
{
    QToolBar *appBar = new QToolBar(this);
    appBar->addAction(publishAct);

    QToolBar *editBar = new QToolBar(this);

    addToolBar(appBar);
    addToolBarBreak();
    addToolBar(editBar);
}

void MainWindow::createStatusBar()
{
    QStatusBar *bar = this->statusBar();

    msgLabel = new QLabel(bar);
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    bar->addWidget(msgLabel);
}
