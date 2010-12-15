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

#ifndef VISUALEDITOR_H
#define VISUALEDITOR_H

#include <QWebView>

/*!
   \class VisualEditor
   \brief The visual editor.
   Visual editor is the WYSIWYG editor. It is the default
   editor of OrbitsWriter.
 */

class VisualEditor : public QWebView
{
    Q_OBJECT
public:
    explicit VisualEditor(QWidget *parent = 0);

signals:

public slots:
    /*!
       \brief Initializes a blank page. The blank page can be used
       when new a page.
     */
    void initBlankPage();

    /*!
       \brief Formats text font.
       \param font selected font
     */
    void formatTextFont(const QFont &font);

    /*!
       \brief Formats text color.
       \param color selected text color
     */
    void formatTextColor(const QColor &color);

    /*!
       \brief Formats text background color.
       \param color selected text background color
     */
    void formatTextBackgroundColor(const QColor &color);

private:
    /*!
       \brief Executes command.
       \param cmd command
     */
    void execCommand(const QString &cmd);

    /*!
       \brief Executes command.
       \param cmd command
       \param arg argument for the command
     */
    void execCommand(const QString &cmd, const QString &arg);

};

#endif // VISUALEDITOR_H
