//
// Copyright (C) 2006-2010  by the original authors of Galaxy
// and all its contributors ("Galaxy.org").
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QTabWidget;
class VisualEditor;
class QTextEdit;
class PluginManager;
class QSignalMapper;
class QTextCharFormat;

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

signals:
    /*!
       \brief Emits when user selected a different font.
       \param font font user selected
     */
    void fontChange(const QFont &font);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void currentCharFormatChanged(const QTextCharFormat &format);
    void showPluginDialog();
    void showFontDialog();

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
    QAction *olAct;
    QAction *ulAct;
    QAction *tableAct;
    QAction *justifyCenterAct;
    QAction *justifyFillAct;
    QAction *justifyLeftAct;
    QAction *justifyRightAct;

    /*
     * web actions
     */
    QAction *publishAct;

    QTabWidget *editorStack;
    VisualEditor *visualEditor;
    QTextEdit *previewEditor;
    QTextEdit *sourceEditor;

    PluginManager *pluginManager;
    QSignalMapper *textFormatMapper;

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createEditors();
    void cursorPositionFontChanged(const QFont &font);
};

#endif // MAINWINDOW_H
