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

class QAction;
class QActionGroup;
class QTabWidget;
class VisualEditor;
class SourceEditor;
class QTextEdit;
class PluginManager;
class QTextCharFormat;
class QDockWidget;

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

    /*!
       \brief Emits when user selected a different text color.
       \param color text color user selected
     */
    void textColorChange(const QColor &color);

    /*!
       \brief Emits when user selected a different nackground color.
       \param color text background color user selected
     */
    void textBackgroundColorChange(const QColor &color);

    /*!
       \brief Emits when text alignment changed.
       \param align text alignment value
     */
    void textAlignmentChange(Qt::Alignment align);

public slots:

    /*!
       \brief Actives this main window.
       \param message message passed from \a main()
     */
    void activeWindow(const QString &message);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void currentCharFormatChanged(const QTextCharFormat &format);
    void textAlignmentChanged(QAction *act);
    void showPluginDialog();
    void showFontDialog();
    void showTextColorDialog();
    void showTextBackgroundColorDialog();
    void editorChanged(int idx);
    void visualEditorCursorPositionChanged();

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
    QAction *tableAct;

    QActionGroup *alignGroup;
    QAction *alignCenterAct;
    QAction *alignJustifyAct;
    QAction *alignLeftAct;
    QAction *alignRightAct;

    /*
     * web actions
     */
    QAction *publishAct;

    QTabWidget *editorStack;
    VisualEditor *visualEditor;
    QTextEdit *previewEditor;
    SourceEditor *sourceEditor;
    QDockWidget *dockWidget;

    PluginManager *pluginManager;

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createEditors();
    void createDockWidget();
    void createConnections();
    void currentFontChanged(const QFont &font);
    void currentTextColorChanged(const QColor &color);
    void currentTextBackgroundColorChanged(const QColor &color);
};

#endif // MAINWINDOW_H
