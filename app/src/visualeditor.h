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

#ifndef VISUALEDITOR_H
#define VISUALEDITOR_H

#include <QTextEdit>

class QAction;

/*!
   \class VisualEditor
   \brief The visual editor.
   Visual editor is the WYSIWYG editor. It is the default
   editor of OrbitsWriter.
 */

class VisualEditor : public QTextEdit
{
    Q_OBJECT
public:
    explicit VisualEditor(QWidget *parent = 0);

signals:

public slots:
    void fontChanged(const QFont& font);
    void textColorChanged(const QColor& color);
    void textBackgroundColorChanged(const QColor& color);
    void setTextBold(bool value);
    void setTextItalic(bool value);
    void setTextUnderline(bool value);
    void setTextStrike(bool value);

private:
    void applyFormat(const QTextCharFormat &format);

};

#endif // VISUALEDITOR_H
