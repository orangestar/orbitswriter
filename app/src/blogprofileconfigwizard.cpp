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

#include "blogprofileconfigwizard.h"
#include "profilemanager.h"

using namespace orbitswriter;

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
    BlogProfile profile;
    profile.blogAddr = field("blogAddress").toString();
    profile.userName = field("userName").toString();
    profile.password = field("password").toString();
    profile.rememberPassword = field("rememberPassword").toBool();
    profile.blogType = field("blogType").toString();
    profile.publishUrl = field("publishUrl").toString();
    profile.profileName = field("blogProfileName").toString();

    ProfileManager *pmgr = ProfileManager::instance();
    pmgr->saveBlogProfile(profile);
    // QMessageBox::information(0, "", QString("%1\n%2\n%3\n%4\n%5\n%6\n%7").arg(blogAddr, userName, pwd, remPwd?"true":"false", blogType, publishUrl, profileName));

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
    registerField("blogAddress", addrInput);

    QLabel *userNameLabel = new QLabel(tr("&User name: "), this);
    QLineEdit *userNameInput = new QLineEdit(this);
    userNameInput->setMaximumWidth(150);
    userNameLabel->setBuddy(userNameInput);
    layout->addWidget(userNameLabel);
    layout->addWidget(userNameInput);
    registerField("userName", userNameInput);

    QLabel *passwordLabel = new QLabel(tr("&Password: "), this);
    QLineEdit *passwordInput = new QLineEdit(this);
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setMaximumWidth(150);
    passwordLabel->setBuddy(passwordInput);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordInput);
    registerField("password", passwordInput);

    QCheckBox *remPwdBox = new QCheckBox(tr("&Remember my password."), this);
    layout->addWidget(remPwdBox);
    registerField("rememberPassword", remPwdBox);
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
    registerField("publishUrl", urlInput);
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
    registerField("blogProfileName", nameInput);
}
