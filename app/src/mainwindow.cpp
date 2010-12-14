//
// Copyright (C) 2006-2010  by the original authors of Galaxy
// and all its contributors ("Galaxy.org").
//
// This file is part of OrbitsWriter.
//
// OrbitsWriter is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OrbitsWriter is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with OrbitsWriter.  If not, see <http://www.gnu.org/licenses/>.
//

#include <QtGui>
#include <QtWebKit>

#include "mainwindow.h"
#include "appcontext.h"
#include "visualeditor.h"
#include "sourceeditor.h"

#define FORWARD_ACTION(act1, act2) \
    connect(act1, SIGNAL(triggered()), visualEditor->pageAction(act2), SLOT(trigger())); \
    connect(visualEditor->pageAction(act2), SIGNAL(changed()), this, SLOT(applyFormat()));

#define APPLY_ENABLED(act1, act2) \
    act1->setEnabled(visualEditor->pageAction(act2)->isEnabled())

#define APPLY_CHECKED(act1, act2) \
    act1->setChecked(visualEditor->pageAction(act2)->isChecked())

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWidget();
    createEditors();
    createConnections();

    visualEditor->setFocus();
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
    alignGroup = new QActionGroup(this);

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
    savePostAct->setEnabled(false);
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

    redoAct = new QAction(QIcon(":/img/redo"), tr("Redo"), this);
    redoAct->setShortcut(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo."));
    redoAct->setEnabled(false);

    cutAct = new QAction(QIcon(":/img/cut"), tr("Cut"), this);
    cutAct->setShortcut(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut."));
    cutAct->setEnabled(false);

    copyAct = new QAction(QIcon(":/img/copy"), tr("Copy"), this);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy."));
    copyAct->setEnabled(false);

    pasteAct = new QAction(QIcon(":/img/paste"), tr("Paste"), this);
    pasteAct->setShortcut(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste."));

    pluginAct = new QAction(QIcon(":/img/plugin"), tr("Plugins..."), this);
    pluginAct->setStatusTip(tr("Manage plugins."));

    helpAct = new QAction(QIcon(":/img/help"), tr("Help"), this);
    helpAct->setShortcut(QKeySequence::HelpContents);
    helpAct->setStatusTip(tr("Open help contents."));

    aboutAct = new QAction(QIcon(":/img/about"), tr("About"), this);
    aboutAct->setStatusTip(tr("About OrbitsWriter."));

    publishAct = new QAction(QIcon(":/img/publish"), tr("Publish"), this);
    publishAct->setStatusTip(tr("Publish the post."));

    textBoldAct = new QAction(QIcon(":/img/bold"), tr("Bold"), this);
    textBoldAct->setShortcut(Qt::CTRL + Qt::Key_B);
    textBoldAct->setStatusTip(tr("Set text bold."));
    textBoldAct->setCheckable(true);

    textItalicAct = new QAction(QIcon(":/img/italic"), tr("Italic"), this);
    textItalicAct->setShortcut(Qt::CTRL + Qt::Key_I);
    textItalicAct->setStatusTip(tr("Set text italic."));
    textItalicAct->setCheckable(true);

    textUnderlineAct = new QAction(QIcon(":/img/underline"), tr("Underline"), this);
    textUnderlineAct->setShortcut(Qt::CTRL + Qt::Key_U);
    textUnderlineAct->setStatusTip(tr("Add underline."));
    textUnderlineAct->setCheckable(true);

    textStrikeoutAct = new QAction(QIcon(":/img/strike"), tr("Strike"), this);
    textStrikeoutAct->setShortcut(Qt::CTRL + Qt::Key_D);
    textStrikeoutAct->setStatusTip(tr("Strike out."));
    textStrikeoutAct->setCheckable(true);

    textFontAct = new QAction(QIcon(":/img/font"), tr("Font..."), this);
    textFontAct->setStatusTip(tr("Set font."));

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    textColorAct = new QAction(pix, tr("Text Color..."), this);
    textColorAct->setStatusTip(tr("Text color."));

    QPixmap bpix(16, 16);
    bpix.fill(Qt::white);
    textBackgroundColorAct = new QAction(bpix, tr("Text Background Color..."), this);
    textBackgroundColorAct->setStatusTip(tr("Text background color."));

    numberedListAct = new QAction(QIcon(":/img/ol"), tr("Ordered List"), this);
    numberedListAct->setStatusTip(tr("Add ordered list."));
    numberedListAct->setCheckable(true);

    bulletListAct = new QAction(QIcon(":/img/ul"), tr("Bullet List"), this);
    bulletListAct->setStatusTip(tr("Add bullet list."));
    bulletListAct->setCheckable(true);

    indentMoreAct = new QAction(QIcon(":/img/indent_more"), tr("Indent More"), this);
    indentMoreAct->setStatusTip(tr("Indent list more."));
    indentMoreAct->setShortcut(Qt::Key_Tab);

    indentLessAct = new QAction(QIcon(":/img/indent_less"), tr("Indent Less"), this);
    indentLessAct->setStatusTip(tr("Indent list less."));
    indentLessAct->setShortcut(Qt::CTRL + Qt::Key_Backspace);

    tableInsertAct = new QAction(QIcon(":/img/table"), tr("Add Table..."), this);
    tableInsertAct->setStatusTip(tr("Add table."));

    tablePropAct = new QAction(QIcon(":/img/table_prop"), tr("Table properties..."), this);
    tablePropAct->setStatusTip(tr("Table properties."));

    tableRowPropAct = new QAction(tr("Row properties..."), this);
    tableRowPropAct->setStatusTip(tr("Table row properties."));

    tableColPropAct = new QAction(tr("Column properties..."), this);
    tableColPropAct->setStatusTip(tr("Table column properties."));

    tableCellPropAct = new QAction(tr("Cell properties..."), this);
    tableCellPropAct->setStatusTip(tr("Table cell properties."));

    tableInsertRowUpAct = new QAction(QIcon(":/img/add_row_up"), tr("Insert Row Upside"), this);
    tableInsertRowUpAct->setStatusTip(tr("Insert a row at upside of selected."));

    tableInsertRowDownAct = new QAction(QIcon(":/img/add_row_down"), tr("Insert Row Downside"), this);
    tableInsertRowDownAct->setStatusTip(tr("Insert a row at downside of selected."));

    tableInsertColLeftAct = new QAction(QIcon(":/img/add_col_left"), tr("Insert Column Leftside"), this);
    tableInsertColLeftAct->setStatusTip(tr("Insert a column at leftside of selected."));

    tableInsertColRightAct = new QAction(QIcon(":/img/add_col_right"), tr("Insert Column Rightside"), this);
    tableInsertColRightAct->setStatusTip(tr("Insert a column at rightside of selected."));

    tableRowUpAct = new QAction(QIcon(":/img/row_up"), tr("Move Row Upside"), this);
    tableRowUpAct->setStatusTip(tr("Move selected row upside."));

    tableRowDownAct = new QAction(QIcon(":/img/row_down"), tr("Move Row Downside"), this);
    tableRowDownAct->setStatusTip(tr("Move selected row downside."));

    tableColLeftAct = new QAction(QIcon(":/img/col_left"), tr("Move Column Leftside"), this);
    tableColLeftAct->setStatusTip(tr("Move selected column leftside."));

    tableColRightAct = new QAction(QIcon(":/img/col_right"), tr("Move Column Rightside"), this);
    tableColRightAct->setStatusTip(tr("Move selected column rightside."));

    tableDelAct = new QAction(QIcon(":/img/del_table"), tr("Delete Table"), this);
    tableDelAct->setStatusTip(tr("Delete table."));

    tableDelRowAct = new QAction(QIcon(":/img/del_row"), tr("Delete Row"), this);
    tableDelRowAct->setStatusTip(tr("Delete row."));

    tableDelColAct = new QAction(QIcon(":/img/del_col"), tr("Delete Column"), this);
    tableDelColAct->setStatusTip(tr("Delete column."));

    tableCellClearAct = new QAction(QIcon(":/img/clear_cell"), tr("Clear Cell"), this);
    tableCellClearAct->setStatusTip(tr("Clear cell."));

    alignCenterAct = new QAction(QIcon(":/img/justify_center"), tr("Center"), this);
    alignCenterAct->setStatusTip(tr("Justify center."));
    alignCenterAct->setShortcut(Qt::CTRL + Qt::Key_E);
    alignCenterAct->setCheckable(true);
    alignGroup->addAction(alignCenterAct);

    alignJustifyAct = new QAction(QIcon(":/img/justify_fill"), tr("Fill"), this);
    alignJustifyAct->setStatusTip(tr("Justify fill."));
    alignJustifyAct->setShortcut(Qt::CTRL + Qt::Key_F);
    alignJustifyAct->setCheckable(true);
    alignJustifyAct->setChecked(true);
    alignGroup->addAction(alignJustifyAct);

    alignLeftAct = new QAction(QIcon(":/img/justify_left"), tr("Left"), this);
    alignLeftAct->setStatusTip(tr("Justify left."));
    alignLeftAct->setShortcut(Qt::CTRL + Qt::Key_L);
    alignLeftAct->setCheckable(true);
    alignGroup->addAction(alignLeftAct);

    alignRightAct = new QAction(QIcon(":/img/justify_right"), tr("Right"), this);
    alignRightAct->setStatusTip(tr("Justify Right."));
    alignRightAct->setShortcut(Qt::CTRL + Qt::Key_R);
    alignRightAct->setCheckable(true);
    alignGroup->addAction(alignRightAct);
}

QMenu* MainWindow::createTableMenu(QWidget *parent /* = 0 */)
{
    QMenu *tableMenu = new QMenu(tr("Table"), parent);
    tableMenu->addAction(tableInsertAct);
    tableMenu->addSeparator();
    tableMenu->addAction(tablePropAct);
    tableMenu->addAction(tableRowPropAct);
    tableMenu->addAction(tableColPropAct);
    tableMenu->addAction(tableCellPropAct);
    tableMenu->addAction(tableCellPropAct);
    tableMenu->addSeparator();
    tableMenu->addAction(tableInsertRowUpAct);
    tableMenu->addAction(tableInsertRowDownAct);
    tableMenu->addAction(tableRowUpAct);
    tableMenu->addAction(tableRowDownAct);
    tableMenu->addSeparator();
    tableMenu->addAction(tableInsertColLeftAct);
    tableMenu->addAction(tableInsertColRightAct);
    tableMenu->addAction(tableColLeftAct);
    tableMenu->addAction(tableColRightAct);
    tableMenu->addSeparator();
    tableMenu->addAction(tableDelAct);
    tableMenu->addAction(tableDelRowAct);
    tableMenu->addAction(tableDelColAct);
    tableMenu->addSeparator();
    tableMenu->addAction(tableCellClearAct);
    return tableMenu;
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

    QMenu *formatMenu = new QMenu(tr("F&ormat"), bar);
    formatMenu->addAction(textFontAct);
    formatMenu->addAction(textColorAct);
    formatMenu->addAction(textBackgroundColorAct);
    formatMenu->addSeparator();
    QMenu *alignMenu = new QMenu(tr("Alignment"), formatMenu);
    if(QApplication::isLeftToRight()) {
        alignMenu->addAction(alignLeftAct);
        alignMenu->addAction(alignCenterAct);
        alignMenu->addAction(alignRightAct);
    } else {
        alignMenu->addAction(alignRightAct);
        alignMenu->addAction(alignCenterAct);
        alignMenu->addAction(alignLeftAct);
    }
    alignMenu->addAction(alignJustifyAct);
    formatMenu->addMenu(alignMenu);
    bar->addMenu(formatMenu);

    QMenu *insertMenu = new QMenu(tr("&Insert"), bar);
    QMenu *listMenu = new QMenu(tr("List"), insertMenu);
    listMenu->addAction(bulletListAct);
    listMenu->addAction(numberedListAct);
    listMenu->addSeparator();
    listMenu->addAction(indentMoreAct);
    listMenu->addAction(indentLessAct);
    insertMenu->addMenu(listMenu);
    QMenu *tableMenu = createTableMenu(insertMenu);
    insertMenu->addMenu(tableMenu);
    bar->addMenu(insertMenu);

    QMenu *toolMenu = new QMenu(tr("&Tools"), bar);
    toolMenu->addAction(pluginAct);
    bar->addMenu(toolMenu);

    bar->addSeparator();

    QMenu *helpMenu = new QMenu(tr("&Help"), bar);
    helpMenu->addAction(helpAct);
    helpMenu->addAction(aboutAct);
    bar->addMenu(helpMenu);
}

void MainWindow::createToolBars()
{
    webToolBar = addToolBar(tr("Web Tool Bar"));
    webToolBar->addAction(publishAct);

    editToolBar = addToolBar(tr("Edit Tool Bar"));
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    QToolButton *editButton = new QToolButton(editToolBar);
    QMenu *editList = new QMenu(editButton);
    editList->addAction(cutAct);
    editList->addAction(copyAct);
    editList->addAction(pasteAct);
    editButton->setPopupMode(QToolButton::InstantPopup);
    editButton->setIcon(cutAct->icon());
    editButton->setMenu(editList);
    editToolBar->addWidget(editButton);

    textToolBar = addToolBar(tr("Text Tool Bar"));
    QComboBox *secList = new QComboBox(this);
    secList->addItem(tr("p"));
    secList->addItem(tr("h1"));
    secList->addItem(tr("h2"));
    secList->addItem(tr("h3"));
    secList->addItem(tr("h4"));
    secList->addItem(tr("h5"));
    secList->addItem(tr("h6"));
    textToolBar->addWidget(secList);
    textToolBar->addAction(textBoldAct);
    textToolBar->addAction(textItalicAct);
    textToolBar->addAction(textUnderlineAct);
    textToolBar->addAction(textStrikeoutAct);
    textToolBar->addAction(textFontAct);
    textToolBar->addAction(textColorAct);
    textToolBar->addAction(textBackgroundColorAct);
    textToolBar->addSeparator();
    if(QApplication::isLeftToRight()) {
        textToolBar->addAction(alignLeftAct);
        textToolBar->addAction(alignCenterAct);
        textToolBar->addAction(alignRightAct);
    } else {
        textToolBar->addAction(alignRightAct);
        textToolBar->addAction(alignCenterAct);
        textToolBar->addAction(alignLeftAct);
    }
    textToolBar->addAction(alignJustifyAct);
    textToolBar->addSeparator();
    textToolBar->addAction(bulletListAct);
    textToolBar->addAction(numberedListAct);
    QToolButton *tableButton = new QToolButton(editToolBar);
    tableButton->setMenu(createTableMenu(tableButton));
    tableButton->setPopupMode(QToolButton::InstantPopup);
    tableButton->setIcon(tableInsertAct->icon());
    tableButton->setToolTip(tr("Table"));
    textToolBar->addWidget(tableButton);
}

void MainWindow::createStatusBar()
{
    QStatusBar *bar = this->statusBar();
    bar->showMessage(tr("Ready."));
}

void MainWindow::createDockWidget()
{
    dockWidget = new QDockWidget(tr("Insert"), this);
    dockWidget->setMinimumWidth(200);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);
}

void MainWindow::createEditors()
{
    editorStack = new QTabWidget(this);
    visualEditor = new VisualEditor(editorStack);
    editorStack->addTab(visualEditor, tr("Visual"));

    previewEditor = new QWidget(editorStack);
    editorStack->addTab(previewEditor, tr("Preview"));

    sourceEditor = new SourceEditor(editorStack);
    editorStack->addTab(sourceEditor, tr("Source"));

    editorStack->setTabPosition(QTabWidget::South);
}

void MainWindow::activeWindow(const QString &message)
{
    Q_UNUSED(message);
    QApplication::alert(this);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
//    if (continueToClose()) {
        AppContext::instance()->saveData();
        event->accept();
//    } else {
//        event->ignore();
//    }
}

void MainWindow::applyFormat()
{
    APPLY_ENABLED(undoAct, QWebPage::Undo);
    APPLY_ENABLED(redoAct, QWebPage::Redo);
    APPLY_ENABLED(cutAct, QWebPage::Cut);
    APPLY_ENABLED(copyAct, QWebPage::Copy);
    APPLY_ENABLED(pasteAct, QWebPage::Paste);
    APPLY_CHECKED(textBoldAct, QWebPage::ToggleBold);
    APPLY_CHECKED(textItalicAct, QWebPage::ToggleItalic);
    APPLY_CHECKED(textUnderlineAct, QWebPage::ToggleUnderline);
    APPLY_CHECKED(textStrikeoutAct, QWebPage::ToggleStrikethrough);
}

void MainWindow::createConnections()
{
    FORWARD_ACTION(undoAct, QWebPage::Undo);
    FORWARD_ACTION(redoAct, QWebPage::Redo);
    FORWARD_ACTION(cutAct, QWebPage::Cut);
    FORWARD_ACTION(copyAct, QWebPage::Copy);
    FORWARD_ACTION(pasteAct, QWebPage::Paste);
    FORWARD_ACTION(textBoldAct, QWebPage::ToggleBold);
    FORWARD_ACTION(textItalicAct, QWebPage::ToggleItalic);
    FORWARD_ACTION(textUnderlineAct, QWebPage::ToggleUnderline);
    FORWARD_ACTION(textStrikeoutAct, QWebPage::ToggleStrikethrough);
}
