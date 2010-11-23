#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QToolButton>
#include <QLabel>

#include "mainwindow.h"
#include "editorstack.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    editor = new EditorStack(this);

    this->setWindowIcon(QIcon(":/img/orbitswriter"));
    this->setCentralWidget(editor);
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    newPostAct = new QAction(QIcon(":/img/doc_new"), tr("&New"), this);
    newPostAct->setShortcut(QKeySequence::New);
    newPostAct->setStatusTip(tr("Create a new post."));

    openPostAct = new QAction(QIcon(":/img/open"), tr("&Open..."), this);
    openPostAct->setShortcut(QKeySequence::Open);
    openPostAct->setStatusTip(tr("Open a post."));

    closePostAct = new QAction(QIcon(":/img/doc_close"), tr("Close"), this);
    closePostAct->setShortcut(QKeySequence::Close);
    closePostAct->setStatusTip(tr("Close the post."));

    savePostAct = new QAction(QIcon(":/img/save"), tr("Save"), this);
    savePostAct->setShortcut(QKeySequence::Save);
    savePostAct->setStatusTip(tr("Save the post."));

    saveAsPostAct = new QAction(QIcon(":/img/save_as"), tr("Save As"), this);
    saveAsPostAct->setShortcut(QKeySequence::SaveAs);
    saveAsPostAct->setStatusTip(tr("Save the post as another one."));

    exitAct = new QAction(QIcon(":/img/exit"), tr("E&xit..."), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit OrbitsWriter."));

    undoAct = new QAction(QIcon(":/img/undo"), tr("Undo"), this);
    undoAct->setShortcut(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo."));

    redoAct = new QAction(QIcon(":/img/redo"), tr("Redo"), this);
    redoAct->setShortcut(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo."));

    cutAct = new QAction(QIcon(":/img/cut"), tr("Cut"), this);
    cutAct->setShortcut(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut."));

    copyAct = new QAction(QIcon(":/img/copy"), tr("Copy"), this);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy."));

    pasteAct = new QAction(QIcon(":/img/paste"), tr("Paste"), this);
    pasteAct->setShortcut(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste."));

    helpAct = new QAction(QIcon(":/img/help"), tr("Help"), this);
    helpAct->setShortcut(QKeySequence::HelpContents);
    helpAct->setStatusTip(tr("Open help contents."));

    aboutAct = new QAction(QIcon(":/img/about"), tr("About"), this);
    aboutAct->setStatusTip(tr("About OrbitsWriter."));

    publishAct = new QAction(QIcon(":/img/publish"), tr("Publish"), this);
    publishAct->setStatusTip(tr("Publish the post."));

    textBoldAct = new QAction(QIcon(":/img/bold"), tr("Bold"), this);
    textBoldAct->setStatusTip(tr("Set text bold."));

    textItalicAct = new QAction(QIcon(":/img/italic"), tr("Italic"), this);
    textItalicAct->setStatusTip(tr("Set text italic."));

    textUnderlineAct = new QAction(QIcon(":/img/underline"), tr("Underline"), this);
    textUnderlineAct->setStatusTip(tr("Add underline."));

    textStrikeoutAct = new QAction(QIcon(":/img/strike"), tr("Strike"), this);
    textStrikeoutAct->setStatusTip(tr("Strike out."));

    textFontAct = new QAction(QIcon(":/img/font"), tr("Font"), this);
    textFontAct->setStatusTip(tr("Set font."));

    olAct = new QAction(QIcon(":/img/ol"), tr("Ordered list"), this);
    olAct->setStatusTip(tr("Add ordered list."));

    ulAct = new QAction(QIcon(":/img/ul"), tr("Unordered list"), this);
    ulAct->setStatusTip(tr("Add unordered list."));

    tableAct = new QAction(QIcon(":/img/table"), tr("Table"), this);
    tableAct->setStatusTip(tr("Add table."));

    justifyCenterAct = new QAction(QIcon(":/img/justify_center"), tr("Center"), this);
    justifyCenterAct->setStatusTip(tr("Justify center."));

    justifyFillAct = new QAction(QIcon(":/img/justify_fill"), tr("Fill"), this);
    justifyFillAct->setStatusTip(tr("Justify fill."));

    justifyLeftAct = new QAction(QIcon(":/img/justify_left"), tr("Left"), this);
    justifyLeftAct->setStatusTip(tr("Justify left."));

    justifyRightAct = new QAction(QIcon(":/img/justify_right"), tr("Right"), this);
    justifyRightAct->setStatusTip(tr("Justify Right."));
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
    QToolBar *bar = new QToolBar(this);
    bar->addAction(publishAct);
    bar->addSeparator();
    QMenu *editList = new QMenu(bar);
    editList->addAction(cutAct);
    editList->addAction(copyAct);
    editList->addAction(pasteAct);
    QToolButton *editButton = new QToolButton(bar);
    editButton->setPopupMode(QToolButton::InstantPopup);
    editButton->setIcon(cutAct->icon());
    editButton->setMenu(editList);
    bar->addWidget(editButton);
    bar->addSeparator();
    bar->addAction(textBoldAct);
    bar->addAction(textItalicAct);
    bar->addAction(textUnderlineAct);
    bar->addAction(textStrikeoutAct);
    bar->addAction(textFontAct);
    bar->addSeparator();
    bar->addAction(olAct);
    bar->addAction(ulAct);
    bar->addAction(tableAct);
    bar->addSeparator();
    bar->addAction(justifyCenterAct);
    bar->addAction(justifyFillAct);
    bar->addAction(justifyLeftAct);
    bar->addAction(justifyRightAct);

    addToolBar(bar);
}

void MainWindow::createStatusBar()
{
    QStatusBar *bar = this->statusBar();

    msgLabel = new QLabel(bar);
    msgLabel->setText(tr("Welcome to OrbitsWriter."));
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    bar->addWidget(msgLabel);
}
