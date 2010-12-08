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

#include <QDebug>
#include <QApplication>
#include <QAction>
#include <QActionGroup>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QToolButton>
#include <QLabel>
#include <QTabWidget>
#include <QTextEdit>
#include <QMessageBox>
#include <QFontDialog>
#include <QCloseEvent>
#include <QColorDialog>
#include <QDockWidget>
#include <QTextList>
#include <QTextListFormat>

#include "common.h"
#include "mainwindow.h"
#include "visualeditor.h"
#include "pluginmanager.h"
#include "appcontext.h"
#include "sourceeditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      pluginManager(PluginManager::instance())
{
    pluginManager->loadPlugins();

    createEditors();
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWidget();

    visualEditor->setFocus();
    setCentralWidget(editorStack);
    setWindowTitle(tr("OrbitsWriter [*]"));
    setWindowIcon(QIcon(":/img/orbitswriter"));
    setUnifiedTitleAndToolBarOnMac(true);

    connect(this, SIGNAL(fontChange(QFont)), visualEditor, SLOT(fontChanged(QFont)));
    connect(this, SIGNAL(textColorChange(QColor)), visualEditor, SLOT(textColorChanged(QColor)));
    connect(this, SIGNAL(textBackgroundColorChange(QColor)), visualEditor, SLOT(textBackgroundColorChanged(QColor)));
    connect(this, SIGNAL(textAlignmentChange(Qt::Alignment)), visualEditor, SLOT(textAlignmentChanged(Qt::Alignment)));
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
    savePostAct->setEnabled(false);
    savePostAct->setShortcut(QKeySequence::Save);
    savePostAct->setStatusTip(tr("Save the post."));
    connect(visualEditor->document(), SIGNAL(modificationChanged(bool)), savePostAct, SLOT(setEnabled(bool)));
    connect(sourceEditor->document(), SIGNAL(modificationChanged(bool)), savePostAct, SLOT(setEnabled(bool)));

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
    connect(visualEditor, SIGNAL(undoAvailable(bool)), undoAct, SLOT(setEnabled(bool)));
    connect(sourceEditor, SIGNAL(undoAvailable(bool)), undoAct, SLOT(setEnabled(bool)));

    redoAct = new QAction(QIcon(":/img/redo"), tr("Redo"), this);
    redoAct->setShortcut(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo."));
    redoAct->setEnabled(false);
    connect(visualEditor, SIGNAL(redoAvailable(bool)), redoAct, SLOT(setEnabled(bool)));
    connect(sourceEditor, SIGNAL(redoAvailable(bool)), redoAct, SLOT(setEnabled(bool)));

    cutAct = new QAction(QIcon(":/img/cut"), tr("Cut"), this);
    cutAct->setShortcut(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut."));
    cutAct->setEnabled(false);
    connect(visualEditor, SIGNAL(copyAvailable(bool)), cutAct, SLOT(setEnabled(bool)));
    connect(sourceEditor, SIGNAL(copyAvailable(bool)), cutAct, SLOT(setEnabled(bool)));

    copyAct = new QAction(QIcon(":/img/copy"), tr("Copy"), this);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy."));
    copyAct->setEnabled(false);
    connect(visualEditor, SIGNAL(copyAvailable(bool)), copyAct, SLOT(setEnabled(bool)));
    connect(sourceEditor, SIGNAL(copyAvailable(bool)), copyAct, SLOT(setEnabled(bool)));

    pasteAct = new QAction(QIcon(":/img/paste"), tr("Paste"), this);
    pasteAct->setShortcut(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste."));

    pluginAct = new QAction(QIcon(":/img/plugin"), tr("Plugins..."), this);
    pluginAct->setStatusTip(tr("Manage plugins."));
    connect(pluginAct, SIGNAL(triggered()), this, SLOT(showPluginDialog()));

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
    connect(textBoldAct, SIGNAL(triggered(bool)), visualEditor, SLOT(setTextBold(bool)));

    textItalicAct = new QAction(QIcon(":/img/italic"), tr("Italic"), this);
    textItalicAct->setShortcut(Qt::CTRL + Qt::Key_I);
    textItalicAct->setStatusTip(tr("Set text italic."));
    textItalicAct->setCheckable(true);
    connect(textItalicAct, SIGNAL(triggered(bool)), visualEditor, SLOT(setTextItalic(bool)));

    textUnderlineAct = new QAction(QIcon(":/img/underline"), tr("Underline"), this);
    textUnderlineAct->setShortcut(Qt::CTRL + Qt::Key_U);
    textUnderlineAct->setStatusTip(tr("Add underline."));
    textUnderlineAct->setCheckable(true);
    connect(textUnderlineAct, SIGNAL(triggered(bool)), visualEditor, SLOT(setTextUnderline(bool)));

    textStrikeoutAct = new QAction(QIcon(":/img/strike"), tr("Strike"), this);
    textStrikeoutAct->setShortcut(Qt::CTRL + Qt::Key_D);
    textStrikeoutAct->setStatusTip(tr("Strike out."));
    textStrikeoutAct->setCheckable(true);
    connect(textStrikeoutAct, SIGNAL(triggered(bool)), visualEditor, SLOT(setTextStrike(bool)));

    textFontAct = new QAction(QIcon(":/img/font"), tr("Font..."), this);
    textFontAct->setStatusTip(tr("Set font."));
    connect(textFontAct, SIGNAL(triggered()), this, SLOT(showFontDialog()));

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    textColorAct = new QAction(pix, tr("Text Color..."), this);
    textColorAct->setStatusTip(tr("Text color."));
    connect(textColorAct, SIGNAL(triggered()), this, SLOT(showTextColorDialog()));

    QPixmap bpix(16, 16);
    bpix.fill(Qt::white);
    textBackgroundColorAct = new QAction(bpix, tr("Text Background Color..."), this);
    textBackgroundColorAct->setStatusTip(tr("Text background color."));
    connect(textBackgroundColorAct, SIGNAL(triggered()), this, SLOT(showTextBackgroundColorDialog()));

    numberedListAct = new QAction(QIcon(":/img/ol"), tr("Ordered list"), this);
    numberedListAct->setStatusTip(tr("Add ordered list."));
    numberedListAct->setCheckable(true);

    bulletListAct = new QAction(QIcon(":/img/ul"), tr("Bullet list"), this);
    bulletListAct->setStatusTip(tr("Add bullet list."));
    bulletListAct->setCheckable(true);
    connect(bulletListAct, SIGNAL(triggered(bool)), visualEditor, SLOT(insertBulletList(bool)));

    tableAct = new QAction(QIcon(":/img/table"), tr("Table"), this);
    tableAct->setStatusTip(tr("Add table."));

    QActionGroup *alignGroup = new QActionGroup(this);
    connect(alignGroup, SIGNAL(triggered(QAction*)), this, SLOT(textAlignmentChanged(QAction*)));

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
    formatMenu->addSeparator();
    formatMenu->addAction(bulletListAct);
    formatMenu->addAction(numberedListAct);
    bar->addMenu(formatMenu);

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
    textToolBar->addAction(tableAct);
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
    connect(visualEditor, SIGNAL(currentCharFormatChanged(QTextCharFormat)),
            this, SLOT(currentCharFormatChanged(QTextCharFormat)));
    connect(visualEditor, SIGNAL(cursorPositionChanged()),
            this, SLOT(visualEditorCursorPositionChanged()));
    connect(visualEditor->document(), SIGNAL(modificationChanged(bool)), this, SLOT(setWindowModified(bool)));

    previewEditor = new QTextEdit(editorStack);
    editorStack->addTab(previewEditor, tr("Preview"));

    sourceEditor = new SourceEditor(editorStack);
    editorStack->addTab(sourceEditor, tr("Source"));
    connect(sourceEditor->document(), SIGNAL(modificationChanged(bool)), this, SLOT(setWindowModified(bool)));

    editorStack->setTabPosition(QTabWidget::South);
    connect(editorStack, SIGNAL(currentChanged(int)), this, SLOT(editorChanged(int)));
}

void MainWindow::createDockWidget()
{
    dockWidget = new QDockWidget(tr("Insert"), this);
    dockWidget->setMinimumWidth(200);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);
}

void MainWindow::currentCharFormatChanged(const QTextCharFormat &format)
{
    currentFontChanged(format.font());
    currentTextColorChanged(format.foreground().color());
    currentTextBackgroundColorChanged(format.background().color());
}

void MainWindow::visualEditorCursorPositionChanged()
{
    QTextCursor cursor = visualEditor->textCursor();
    if(cursor.currentList()) {
        QTextListFormat listFmt = cursor.currentList()->format();
        bulletListAct->setChecked(listFmt.style() > QTextListFormat::ListDecimal);
        numberedListAct->setChecked(listFmt.style() < QTextListFormat::ListDecimal);
    } else {
        bulletListAct->setChecked(false);
        numberedListAct->setChecked(false);
    }
}

void MainWindow::showPluginDialog()
{
    QMessageBox::information(this, tr("Plugins"),
                             tr("plugins list"));
}

void MainWindow::showFontDialog()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Verdana", 12), this);
    if(ok) {
        emit fontChange(font);
    }
}

void MainWindow::showTextColorDialog()
{
    QColor color = QColorDialog::getColor(visualEditor->textColor(), this);
    if(color.isValid()) {
        emit textColorChange(color);
        currentTextColorChanged(color);
    }
}

void MainWindow::showTextBackgroundColorDialog()
{
    QColor color = QColorDialog::getColor(visualEditor->textBackgroundColor(), this);
    if(color.isValid()) {
        emit textBackgroundColorChange(color);
        currentTextBackgroundColorChanged(color);
    }
}

void MainWindow::currentFontChanged(const QFont &font)
{
    textBoldAct->setChecked(font.bold());
    textItalicAct->setChecked(font.italic());
    textUnderlineAct->setChecked(font.underline());
    textStrikeoutAct->setChecked(font.strikeOut());
}

void MainWindow::currentTextColorChanged(const QColor &color)
{
    QPixmap pix(16, 16);
    pix.fill(color);
    textColorAct->setIcon(pix);
}

void MainWindow::currentTextBackgroundColorChanged(const QColor &color)
{
    QPixmap pix(16, 16);
    pix.fill(color);
    textBackgroundColorAct->setIcon(pix);
}

void MainWindow::textAlignmentChanged(QAction *act)
{
    if(act == alignCenterAct) {
        emit textAlignmentChange(Qt::AlignHCenter);
    } else if(act == alignJustifyAct) {
        emit textAlignmentChange(Qt::AlignJustify);
    } else if(act == alignLeftAct) {
        emit textAlignmentChange(Qt::AlignLeft | Qt::AlignAbsolute);
    } else if(act == alignRightAct) {
        emit textAlignmentChange(Qt::AlignRight | Qt::AlignAbsolute);
    }
}

void MainWindow::activeWindow(const QString &message)
{
    Q_UNUSED(message);
    this->show();
}

void MainWindow::editorChanged(int idx)
{
    switch(idx) {
    case 0: // visual editor
        visualEditor->setHtml(visualEditor->toPlainText());
        break;
    case 1: // previewer
        break;
    case 2: // source editor
        sourceEditor->setPlainText(visualEditor->toHtml());
        break;
    default:
        // no such case
        break;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
//    if (continueToClose()) {
        AppContext::instance()->updateData();
        event->accept();
//    } else {
//        event->ignore();
//    }
}
