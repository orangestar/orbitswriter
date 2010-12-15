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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QActionGroup;
class VisualEditor;
class SourceEditor;

/*!
   \class MainWindow
   \brief Main window of OrbitsWriter
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    /*!
       \brief Actives this main window.
       \param message message passed from \a main()
     */
    void activeWindow(const QString &message);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void applyFormat();
    void showFontDialog();
    void showTextColorDialog();
    void showTextBackgroundColorDialog();

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
     * tools actions
     */
    QAction *pluginAct;

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
    QAction *textColorAct;
    QAction *textBackgroundColorAct;

    QAction *numberedListAct;
    QAction *bulletListAct;
    QAction *indentMoreAct;
    QAction *indentLessAct;
    QAction *tableInsertAct;
    QAction *tablePropAct;
    QAction *tableRowPropAct;
    QAction *tableColPropAct;
    QAction *tableCellPropAct;
    QAction *tableInsertRowUpAct;
    QAction *tableInsertRowDownAct;
    QAction *tableInsertColLeftAct;
    QAction *tableInsertColRightAct;
    QAction *tableRowUpAct;
    QAction *tableRowDownAct;
    QAction *tableColLeftAct;
    QAction *tableColRightAct;
    QAction *tableDelAct;
    QAction *tableDelRowAct;
    QAction *tableDelColAct;
    QAction *tableCellClearAct;

    QAction *alignCenterAct;
    QAction *alignJustifyAct;
    QAction *alignLeftAct;
    QAction *alignRightAct;

    /*
     * web actions
     */
    QAction *publishAct;

    QActionGroup *alignGroup;

    QToolBar *webToolBar;
    QToolBar *editToolBar;
    QToolBar *textToolBar;
    QTabWidget *editorStack;
    VisualEditor *visualEditor;
    QWidget *previewEditor;
    SourceEditor *sourceEditor;
    QDockWidget *dockWidget;

    void createActions();
    void createMenus();
    QMenu* createTableMenu(QWidget *parent = 0);
    void createToolBars();
    void createStatusBar();
    void createDockWidget();
    void createEditors();
    void createConnections();
    void currentTextColorChanged(const QColor &color);
    void currentTextBackgroundColorChanged(const QColor &color);
};

#endif // MAINWINDOW_H
