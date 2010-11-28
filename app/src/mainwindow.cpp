#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QToolButton>
#include <QLabel>
#include <QTabWidget>
#include <QTextEdit>
#include <QMessageBox>
#include <QSignalMapper>

#include "mainwindow.h"
#include "visualeditor.h"
#include "pluginmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      pluginManager(PluginManager::instance()),
      textFormatMapper(new QSignalMapper(this))
{
    pluginManager->loadPlugins();

    createEditors();
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    setCentralWidget(editorStack);
    setWindowTitle(tr("OrbitsWriter [*]"));
    setWindowIcon(QIcon(":/img/orbitswriter"));
    setUnifiedTitleAndToolBarOnMac(true);
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
    undoAct->setEnabled(false);
    connect(visualEditor, SIGNAL(undoAvailable(bool)),
            undoAct, SLOT(setEnabled(bool)));
    connect(sourceEditor, SIGNAL(undoAvailable(bool)),
            undoAct, SLOT(setEnabled(bool)));

    redoAct = new QAction(QIcon(":/img/redo"), tr("Redo"), this);
    redoAct->setShortcut(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo."));
    redoAct->setEnabled(false);
    connect(visualEditor, SIGNAL(redoAvailable(bool)),
            redoAct, SLOT(setEnabled(bool)));
    connect(sourceEditor, SIGNAL(redoAvailable(bool)),
            redoAct, SLOT(setEnabled(bool)));

    cutAct = new QAction(QIcon(":/img/cut"), tr("Cut"), this);
    cutAct->setShortcut(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut."));
    cutAct->setEnabled(false);
    connect(visualEditor, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));
    connect(sourceEditor, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));

    copyAct = new QAction(QIcon(":/img/copy"), tr("Copy"), this);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy."));
    copyAct->setEnabled(false);
    connect(visualEditor, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));
    connect(sourceEditor, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));

    pasteAct = new QAction(QIcon(":/img/paste"), tr("Paste"), this);
    pasteAct->setShortcut(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste."));

    pluginAct = new QAction(QIcon(":/img/plugin"), tr("Plugins..."), this);
    pluginAct->setStatusTip(tr("Manage plugins."));
    connect(pluginAct, SIGNAL(triggered()),
            this, SLOT(showPluginDialog()));

    helpAct = new QAction(QIcon(":/img/help"), tr("Help"), this);
    helpAct->setShortcut(QKeySequence::HelpContents);
    helpAct->setStatusTip(tr("Open help contents."));

    aboutAct = new QAction(QIcon(":/img/about"), tr("About"), this);
    aboutAct->setStatusTip(tr("About OrbitsWriter."));

    publishAct = new QAction(QIcon(":/img/publish"), tr("Publish"), this);
    publishAct->setStatusTip(tr("Publish the post."));

    textBoldAct = new QAction(QIcon(":/img/bold"), tr("Bold"), this);
    textBoldAct->setStatusTip(tr("Set text bold."));
    textFormatMapper->setMapping(textBoldAct, QString("Bold"));
    connect(textBoldAct, SIGNAL(triggered()),
            textFormatMapper, SLOT(map()));

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

    ulAct = new QAction(QIcon(":/img/ul"), tr("Bullet list"), this);
    ulAct->setStatusTip(tr("Add bullet list."));

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

    connect(textFormatMapper, SIGNAL(mapped(QString)),
            visualEditor, SLOT(setTextFormat(QString)));
}

void MainWindow::createMenus()
{
    QMenuBar *bar = this->menuBar();

    QMenu *fileMenu = new QMenu(tr("&File"), bar);
    fileMenu->addAction(newPostAct);
    fileMenu->addAction(openPostAct);
    fileMenu->addAction(closePostAct);
    fileMenu->addSeparator();
    fileMenu->addAction(savePostAct);
    fileMenu->addAction(saveAsPostAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
    bar->addMenu(fileMenu);

    QMenu *editMenu = new QMenu(tr("&Edit"), bar);
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    bar->addMenu(editMenu);

    QMenu *toolMenu = new QMenu(tr("&Tools"), bar);
    toolMenu->addAction(pluginAct);
    bar->addMenu(toolMenu);

    bar->addSeparator();

    QMenu *helpMenu = new QMenu(tr("Help"), bar);
    helpMenu->addAction(helpAct);
    helpMenu->addAction(aboutAct);
    bar->addMenu(helpMenu);
}

void MainWindow::createToolBars()
{
    QToolBar *webToolBar = addToolBar(tr("Web Tool Bar"));
    webToolBar->addAction(publishAct);

    QToolBar *editToolBar = addToolBar(tr("Edit Tool Bar"));
    QToolButton *editButton = new QToolButton(editToolBar);
    QMenu *editList = new QMenu(editButton);
    editList->addAction(cutAct);
    editList->addAction(copyAct);
    editList->addAction(pasteAct);
    editButton->setPopupMode(QToolButton::InstantPopup);
    editButton->setIcon(cutAct->icon());
    editButton->setMenu(editList);
    editToolBar->addWidget(editButton);

    QToolBar *textToolBar = addToolBar(tr("Text Tool Bar"));
    textToolBar->addAction(textBoldAct);
    textToolBar->addAction(textItalicAct);
    textToolBar->addAction(textUnderlineAct);
    textToolBar->addAction(textStrikeoutAct);
    textToolBar->addAction(textFontAct);
    textToolBar->addSeparator();
    textToolBar->addAction(olAct);
    textToolBar->addAction(ulAct);
    textToolBar->addAction(tableAct);
    textToolBar->addSeparator();
    textToolBar->addAction(justifyCenterAct);
    textToolBar->addAction(justifyFillAct);
    textToolBar->addAction(justifyLeftAct);
    textToolBar->addAction(justifyRightAct);
}

void MainWindow::createStatusBar()
{
    QStatusBar *bar = this->statusBar();
    bar->showMessage(tr("Ready."));
}

void MainWindow::createEditors()
{
    editorStack = new QTabWidget(this);
    visualEditor = new VisualEditor(editorStack);
    editorStack->addTab(visualEditor, tr("Visual"));
    connect(visualEditor->document(), SIGNAL(contentsChanged()),
            this, SLOT(docChanged()));

    previewEditor = new QTextEdit(editorStack);
    editorStack->addTab(previewEditor, tr("Preview"));

    sourceEditor = new QTextEdit(editorStack);
    editorStack->addTab(sourceEditor, tr("Source"));
    connect(sourceEditor->document(), SIGNAL(contentsChanged()),
            this, SLOT(docChanged()));

    editorStack->setTabPosition(QTabWidget::South);
}

void MainWindow::docChanged()
{
    bool modified = visualEditor->document()->isModified()
            || sourceEditor->document()->isModified();
    setWindowModified(modified);
}

void MainWindow::showPluginDialog()
{
    QMessageBox::information(this, tr("Plugins"),
                             tr("plugins list"));
}
