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
#include <QWizard>
#include <QWizardPage>

#include "dataobjs.h"

class QAbstractButton;
class QPushButton;
class QDialogButtonBox;
class QListWidgetItem;
class QListWidget;
class QLineEdit;
class QCheckBox;

namespace orbitswriter
{

/*!
   \class BlogProfileConfigWizard
   \brief Blog profile configuration wizard.
 */

class BlogProfileConfigWizard : public QWizard
{
    Q_OBJECT
public:
    /*!
       \brief Constructs a blog profile configuration wizard with the given parent.
       \param parent parent of this wizard
     */
    explicit BlogProfileConfigWizard(QWidget *parent = 0);

    void accept();

    /*!
       \brief Gets the created blog profile.
       \return the created blog profile
     */
    const BlogProfile & blogProfile() const
    {
        return profile;
    }

private:
    BlogProfile profile;
}; // end of class ProfileConfigWizard

/*!
   \class BlogProfileConfigWizardIntroPage
   \brief Introduction page for blog profile configuration wizard.
 */

class BlogProfileConfigWizardIntroPage : public QWizardPage
{
    Q_OBJECT
public:
    /*!
       \brief Constructs a blog profile configuration wizard introduction page with the given parent.
       \param parent parent of this wizard
     */
    explicit BlogProfileConfigWizardIntroPage(QWidget *parent = 0);
}; // end of class BlogProfileConfigWizardIntroPage

/*!
   \class BlogProfileConfigWizardBlogAccountPage
   \brief Blog account page for blog profile configuration wizard.
 */

class BlogProfileConfigWizardBlogAccountPage : public QWizardPage
{
    Q_OBJECT
public:
    /*!
       \brief Constructs a blog profile configuration wizard blog account page with the given parent.
       \param parent parent of this wizard
     */
    explicit BlogProfileConfigWizardBlogAccountPage(QWidget *parent = 0);
}; // end of class BlogProfileConfigWizardBlogAccountPage

/*!
   \class BlogProfileConfigWizardApiTypePage
   \brief API type page for blog profile configuration wizard.
 */

class BlogProfileConfigWizardApiTypePage : public QWizardPage
{
    Q_OBJECT
public:
    /*!
       \brief Constructs a blog profile configuration wizard API type page with the given parent.
       \param parent parent of this wizard
     */
    explicit BlogProfileConfigWizardApiTypePage(QWidget *parent = 0);
}; // end of class BlogProfileConfigWizardApiTypePage

/*!
   \class BlogProfileConfigWizardProfileNamePage
   \brief Introduction page for blog profile configuration wizard.
 */

class BlogProfileConfigWizardProfileNamePage : public QWizardPage
{
    Q_OBJECT
public:
    /*!
       \brief Constructs a blog profile configuration wizard profile name page with the given parent.
       \param parent parent of this wizard
     */
    explicit BlogProfileConfigWizardProfileNamePage(QWidget *parent = 0);
}; // end of class BlogProfileConfigWizardProfileNamePage

/*!
   \class BlogProfileEditor
   \brief Dialog for modifying blog profile.
 */

class BlogProfileEditor : public QDialog
{
    Q_OBJECT
public:
    /*!
       \brief Constructs a dialog for modifying blog profile with the given parent.
       \param parent parent of this dialog
     */
    explicit BlogProfileEditor(BlogProfile p, QWidget *parent = 0);

    /*!
       \brief Gets the blog profile details.
       \return blog profile
     */
    BlogProfile & blogProfile()
    {
        return profile;
    }

public slots:
    void buttonClicked(QAbstractButton *button);

private:
    BlogProfile profile;

    QDialogButtonBox *buttonBox;
    QLineEdit *bpNameInput;
    QLineEdit *uNameInput;
    QLineEdit *pwdInput;
    QLineEdit *bAddrInput;
    QLineEdit *bTypeInput;
    QLineEdit *bUrlInput;
    QCheckBox *pBox;
    QCheckBox *dBox;
}; // end of class BlogProfileEditor

/*!
   \class BlogProfileDialog
   \brief Blog profile management dialog.
 */

class BlogProfileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BlogProfileDialog(QWidget *parent = 0);

private slots:
    void buttonClicked(QAbstractButton *button);
    void listDoubleClicked(QListWidgetItem * item);

private:
    QListWidget *blogProfileListWidget;
    QPushButton *addButton;
    QPushButton *modButton;
    QPushButton *delButton;
    QDialogButtonBox *buttonBox;

    void addBlogProfile();
    void delBlogProfile(const BlogProfile & profile);
    void modifyBlogProfile(const BlogProfile & profile);
    void refreshData();

}; // end of class BlogProfileDialog

} // end of namespace orbitswriter

#endif // BLOGPROFILEDIALOG_H
