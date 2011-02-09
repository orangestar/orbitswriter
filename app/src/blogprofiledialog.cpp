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

#include "blogprofiledialog.h"
#include "profilemanager.h"
#include "common.h"

using namespace orbitswriter;

////////////////////////////////////////////////////////////////////////////////
//
// BlogProfileDialog
//
////////////////////////////////////////////////////////////////////////////////

BlogProfileDialog::BlogProfileDialog(QWidget *parent) :
    QDialog(parent)
{
    blogProfileListWidget = new QListWidget(this);
    refreshData();
    QLabel *listLabel = new QLabel(tr("Existing Blog Profiles"), this);

    addButton = new QPushButton(tr("Add..."), this);
    modButton = new QPushButton(tr("Modify..."), this);
    delButton = new QPushButton(tr("Remove"), this);

    buttonBox = new QDialogButtonBox(Qt::Vertical, this);
    buttonBox->addButton(addButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(modButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(delButton, QDialogButtonBox::ActionRole);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *listLayout = new QVBoxLayout;
    listLayout->addWidget(listLabel);
    listLayout->addWidget(blogProfileListWidget);
    mainLayout->addLayout(listLayout);
    mainLayout->addWidget(buttonBox);

    resize(400, 300);

    connect(buttonBox, SIGNAL(clicked(QAbstractButton*)),
            SLOT(buttonClicked(QAbstractButton*)));
    connect(blogProfileListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
            SLOT(listDoubleClicked(QListWidgetItem *)));
}

void BlogProfileDialog::buttonClicked(QAbstractButton *button)
{
    if(button == modButton) {
        modifyBlogProfile(blogProfileListWidget->currentItem()->data(Qt::UserRole).value<BlogProfile>());
    } else if(button == delButton) {
        delBlogProfile(blogProfileListWidget->currentItem()->data(Qt::UserRole).value<BlogProfile>());
    } else if(button == addButton) {
        addBlogProfile();
    } else if(button == buttonBox->button(QDialogButtonBox::Ok)) {
        QDialog::accept();
    }
}

void BlogProfileDialog::listDoubleClicked(QListWidgetItem * item)
{
    BlogProfile profile = item->data(Qt::UserRole).value<BlogProfile>();
    modifyBlogProfile(profile);
}

void BlogProfileDialog::addBlogProfile()
{
    BlogProfileConfigWizard w(this);
    w.exec();
    if(w.result() == QDialog::Accepted) {
        BlogProfile profile = w.blogProfile();
        QListWidgetItem *item = new QListWidgetItem;
        if(profile.isDefault) {
            QList<QListWidgetItem *> finds = blogProfileListWidget->findItems(Constants::DefaultFlagStringPostfix, Qt::MatchEndsWith);
            if(finds.size() == 1) {
                QListWidgetItem *old = finds.at(0);
                old->setText(old->text().left(old->text().lastIndexOf(Constants::DefaultFlagStringPostfix)));
            }
            item->setText(profile.profileName + Constants::DefaultFlagStringPostfix);
        } else {
            item->setText(profile.profileName);
        }
        QVariant var;
        var.setValue(profile);
        item->setData(Qt::UserRole, var);
        blogProfileListWidget->addItem(item);
        blogProfileListWidget->setCurrentItem(item);
    }
}

void BlogProfileDialog::delBlogProfile(const BlogProfile & profile)
{
    if(QMessageBox::question(NULL,
                             tr("Delete"),
                             tr("Are you sure to delete profile \"%1\"?").arg(profile.profileName),
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::No) == QMessageBox::Yes) {
        if(ProfileManager::instance()->deleteBlogProfile(profile)) {
            refreshData();
        }
    }
}

void BlogProfileDialog::modifyBlogProfile(const BlogProfile & profile)
{

}

void BlogProfileDialog::refreshData()
{
    blogProfileListWidget->clear();
    QList<BlogProfile *> bpList = ProfileManager::instance()->blogProfileList();
    BlogProfile *bp = NULL;
    foreach(bp, bpList) {
        QListWidgetItem *item = new QListWidgetItem(bp->profileName);
        QVariant var;
        var.setValue(*bp);
        item->setData(Qt::UserRole, var);
        blogProfileListWidget->addItem(item);
        if(bp->isDefault) {
            item->setText(bp->profileName + Constants::DefaultFlagStringPostfix);
            blogProfileListWidget->setCurrentItem(item);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// BlogProfileConfigWizard
//
////////////////////////////////////////////////////////////////////////////////

BlogProfileConfigWizard::BlogProfileConfigWizard(QWidget *parent) :
    QWizard(parent)
{
    addPage(new BlogProfileConfigWizardIntroPage(this));
    addPage(new BlogProfileConfigWizardBlogAccountPage(this));
    addPage(new BlogProfileConfigWizardApiTypePage(this));
    addPage(new BlogProfileConfigWizardProfileNamePage(this));
}

void BlogProfileConfigWizard::accept()
{
    profile.blogAddr = field("blogAddress").toString();
    profile.userName = field("userName").toString();
    profile.password = field("password").toString();
    profile.rememberPassword = field("rememberPassword").toBool();
    profile.blogType = field("blogType").toString();
    profile.publishUrl = field("publishUrl").toString();
    profile.profileName = field("blogProfileName").toString();
    profile.isDefault = field("asDefault").toBool();

    ProfileManager::instance()->saveBlogProfile(profile);

    QWizard::accept();
}

////////////////////////////////////////////////////////////////////////////////
//
// BlogProfileConfigWizardIntroPage
//
////////////////////////////////////////////////////////////////////////////////

BlogProfileConfigWizardIntroPage::BlogProfileConfigWizardIntroPage(QWidget *parent /* = 0 */)
    : QWizardPage(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);
    setTitle(tr("Configurate Blog Profile"));

    QLabel *label = new QLabel(tr("This wizard will lead you set up a usable blog profile. "
                                  "After configuration, you can publish your post with OrbitsWriter easily."), this);
    label->setWordWrap(true);
    layout->addWidget(label);
}

////////////////////////////////////////////////////////////////////////////////
//
// BlogProfileConfigWizardBlogAccountPage
//
////////////////////////////////////////////////////////////////////////////////

BlogProfileConfigWizardBlogAccountPage::BlogProfileConfigWizardBlogAccountPage(QWidget *parent /* = 0 */)
    : QWizardPage(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);
    setTitle(tr("Add Blog Account"));

    QLabel *label = new QLabel(tr("Please add your blog account so OrbitsWriter can access. "), this);
    label->setWordWrap(true);
    layout->addWidget(label);

    QLabel *addrLabel = new QLabel(tr("Your blog &address: "), this);
    QLineEdit *addrInput = new QLineEdit(this);
    addrInput->setMaximumWidth(250);
    addrLabel->setBuddy(addrInput);
    layout->addWidget(addrLabel);
    layout->addWidget(addrInput);
    QLabel *commentLabel = new QLabel(tr("This should be the address you access your blog using browsers."), this);
    commentLabel->setStyleSheet("color: #888888");
    layout->addWidget(commentLabel);
    registerField("blogAddress*", addrInput);

    QLabel *userNameLabel = new QLabel(tr("&User name: "), this);
    QLineEdit *userNameInput = new QLineEdit(this);
    userNameInput->setMaximumWidth(150);
    userNameLabel->setBuddy(userNameInput);
    layout->addWidget(userNameLabel);
    layout->addWidget(userNameInput);
    registerField("userName*", userNameInput);

    QLabel *passwordLabel = new QLabel(tr("&Password: "), this);
    QLineEdit *passwordInput = new QLineEdit(this);
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setMaximumWidth(150);
    passwordLabel->setBuddy(passwordInput);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordInput);
    registerField("password*", passwordInput);

    QCheckBox *remPwdBox = new QCheckBox(tr("&Remember my password."), this);
    layout->addWidget(remPwdBox);
    registerField("rememberPassword", remPwdBox);

    QCheckBox *asDefaultBox = new QCheckBox(tr("Set as &default."), this);
    layout->addWidget(asDefaultBox);
    registerField("asDefault", asDefaultBox);
}

////////////////////////////////////////////////////////////////////////////////
//
// BlogProfileConfigWizardApiTypePage
//
////////////////////////////////////////////////////////////////////////////////

BlogProfileConfigWizardApiTypePage::BlogProfileConfigWizardApiTypePage(QWidget *parent /* = 0 */)
    : QWizardPage(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    setTitle(tr("Configurate Blog Profile"));
    setLayout(layout);

    QLabel *label = new QLabel(tr("Please select your blog type."), this);
    layout->addWidget(label);

    QLabel *typeLabel = new QLabel(tr("Your blog &type: "), this);
    QComboBox *typeList = new QComboBox(this);
    typeList->setMaximumWidth(150);
    typeList->addItem(tr("WordPress"));
    typeLabel->setBuddy(typeList);
    layout->addWidget(typeLabel);
    layout->addWidget(typeList);
    registerField("blogType", typeList);

    QLabel *urlLabel = new QLabel(tr("Blog remote publish &URL: "), this);
    QLineEdit *urlInput = new QLineEdit(this);
    urlInput->setMaximumWidth(250);
    urlLabel->setBuddy(urlInput);
    layout->addWidget(urlLabel);
    layout->addWidget(urlInput);
    registerField("publishUrl*", urlInput);
}

////////////////////////////////////////////////////////////////////////////////
//
// BlogProfileConfigWizardProfileNamePage
//
////////////////////////////////////////////////////////////////////////////////

BlogProfileConfigWizardProfileNamePage::BlogProfileConfigWizardProfileNamePage(QWidget *parent /* = 0 */)
    : QWizardPage(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    setTitle(tr("Congratulations"));
    setLayout(layout);

    QLabel *label = new QLabel(tr("Your blog profile has been configurated completely."
                                  "Please ensure you want to save this profile."), this);
    label->setWordWrap(true);
    layout->addWidget(label);

    QLabel *profileNameLabel = new QLabel(tr("Blog profile name: "), this);
    QLineEdit *nameInput = new QLineEdit(this);
    nameInput->setMaximumWidth(150);
    profileNameLabel->setBuddy(nameInput);
    layout->addWidget(profileNameLabel);
    layout->addWidget(nameInput);
    registerField("blogProfileName*", nameInput);
}
