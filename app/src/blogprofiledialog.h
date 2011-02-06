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

#ifndef BLOGPROFILEDIALOG_H
#define BLOGPROFILEDIALOG_H

#include <QDialog>

class QAbstractButton;
class QPushButton;
class QDialogButtonBox;
class QListWidgetItem;
class QListWidget;

namespace orbitswriter
{

struct BlogProfile;

/*!
   \class BlogProfileDialog
   \brief Blog profile management dialog.
 */

class BlogProfileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BlogProfileDialog(QWidget *parent = 0);

    bool shouldReload() const
    {
        return _shouldReload;
    }

private slots:
    void buttonClicked(QAbstractButton *button);
    void listDoubleClicked(QListWidgetItem * item);

private:
    QListWidget *blogProfileListWidget;
    QPushButton *addButton;
    QPushButton *modButton;
    QPushButton *delButton;
    QDialogButtonBox *buttonBox;
    bool _shouldReload;

    void addBlogProfile();
    void delBlogProfile();
    void modifyBlogProfile(BlogProfile & profile);
    void save();

}; // end of class BlogProfileDialog

} // end of namespace orbitswriter

#endif // BLOGPROFILEDIALOG_H
