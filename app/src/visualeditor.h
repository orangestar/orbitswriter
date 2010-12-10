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

    /*!
       \brief Emits when bullet list removes.
       \param r false if list removed
     */
    void bulletListExists(bool r);

public slots:

    /*!
       \brief Changes text font.
       \param font new font
     */
    void fontChanged(const QFont& font);

    /*!
       \brief Changes text color.
       \param color text color
     */
    void textColorChanged(const QColor& color);

    /*!
       \brief Changes text background color.
       \param color text background text
     */
    void textBackgroundColorChanged(const QColor& color);

    /*!
       \brief Changes text alignment.
       \param align text alignment
     */
    void textAlignmentChanged(Qt::Alignment align);

    /*!
       \brief Sets text bold.
       \param value \a true if text should be bold
     */
    void setTextBold(bool value);

    /*!
       \brief Sets text italic.
       \param value \a true if text should be italic
     */
    void setTextItalic(bool value);

    /*!
       \brief Sets text underline.
       \param value \a true if text should be underlined
     */
    void setTextUnderline(bool value);

    /*!
       \brief Sets text strike out.
       \param value \a true if text should be striked out
     */
    void setTextStrike(bool value);

    /*!
       \brief Inserts a bullet list at current cursor.
       \param insert creates and inserts a bullet list into document if is true,
       remove the exists one if false
     */
    void insertBulletList(bool insert);

    /*!
       \brief Inserts a numbered list at current cursor.
       \param insert creates and inserts a numbered list into document if is true,
       remove the exists one if false
     */
    void insertNumberedList(bool insert);

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    void applyFormat(const QTextCharFormat &format);
    void removeListItem(const QTextBlock &block);
    void insertList(QTextListFormat::Style style, bool insert);

};

#endif // VISUALEDITOR_H
