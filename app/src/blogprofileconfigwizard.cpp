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

using namespace orbitswriter;

BlogProfileConfigWizard::BlogProfileConfigWizard(QWidget *parent) :
    QWizard(parent)
{
    addPage(createIntroPage());
    addPage(createBlogAccountPage());
    addPage(createApiTypePage());
    addPage(createProfileNamePage());
}

QWizardPage * BlogProfileConfigWizard::createIntroPage()
{
    QWizardPage *page = new QWizardPage(this);
    QVBoxLayout *layout = new QVBoxLayout(page);
    page->setLayout(layout);
    page->setTitle(tr("Configurate Blog Profile"));

    QLabel *label = new QLabel(tr("This wizard will lead you set up a usable blog profile. "
                                  "After configuration, you can publish your post with OrbitsWriter easily."), page);
    label->setWordWrap(true);
    layout->addWidget(label);

    return page;
}

QWizardPage * BlogProfileConfigWizard::createBlogAccountPage()
{
    QWizardPage *page = new QWizardPage(this);
    QVBoxLayout *layout = new QVBoxLayout(page);
    page->setLayout(layout);

    page->setTitle(tr("Add Blog Account"));

    QLabel *label = new QLabel(tr("Please add your blog account so OrbitsWriter can access. "), page);
    label->setWordWrap(true);
    layout->addWidget(label);

    QLabel *addrLabel = new QLabel(tr("Your blog &address: "), page);
    QLineEdit *addrInput = new QLineEdit(page);
    addrInput->setMaximumWidth(250);
    addrLabel->setBuddy(addrInput);
    layout->addWidget(addrLabel);
    layout->addWidget(addrInput);
    QLabel *commentLabel = new QLabel(tr("This should be the address you access your blog using browsers."));
    commentLabel->setStyleSheet("color: #888888");
    layout->addWidget(commentLabel);

    QLabel *userNameLabel = new QLabel(tr("&User name: "), page);
    QLineEdit *userNameInput = new QLineEdit(page);
    userNameInput->setMaximumWidth(150);
    userNameLabel->setBuddy(userNameInput);
    layout->addWidget(userNameLabel);
    layout->addWidget(userNameInput);

    QLabel *passwordLabel = new QLabel(tr("&Password: "), page);
    QLineEdit *passwordInput = new QLineEdit(page);
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setMaximumWidth(150);
    passwordLabel->setBuddy(passwordInput);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordInput);

    QCheckBox *remPwdBox = new QCheckBox(tr("&Remember my password."), page);
    layout->addWidget(remPwdBox);

    return page;
}

QWizardPage * BlogProfileConfigWizard::createApiTypePage()
{
    QWizardPage *page = new QWizardPage(this);
    QVBoxLayout *layout = new QVBoxLayout(page);
    page->setTitle(tr("Configurate Blog Profile"));
    page->setLayout(layout);

    QLabel *label = new QLabel(tr("Please select your blog type."), page);
    layout->addWidget(label);

    QLabel *typeLabel = new QLabel(tr("Your blog &type: "), this);
    QComboBox *typeList = new QComboBox(page);
    typeList->setMaximumWidth(150);
    typeList->addItem(tr("WordPress"));
    typeLabel->setBuddy(typeList);
    layout->addWidget(typeLabel);
    layout->addWidget(typeList);

    QLabel *urlLabel = new QLabel(tr("Blog remote publish &URL: "), page);
    QLineEdit *urlInput = new QLineEdit(page);
    urlInput->setMaximumWidth(250);
    urlLabel->setBuddy(urlInput);
    layout->addWidget(urlLabel);
    layout->addWidget(urlInput);

    return page;
}

QWizardPage * BlogProfileConfigWizard::createProfileNamePage()
{
    QWizardPage *page = new QWizardPage(this);
    QVBoxLayout *layout = new QVBoxLayout(page);
    page->setTitle(tr("Congratulations"));
    page->setLayout(layout);

    QLabel *label = new QLabel(tr("Your blog profile has been configurated completely."
                                  "Please ensure you want to save this profile."), page);
    label->setWordWrap(true);
    layout->addWidget(label);

    QLabel *profileNameLabel = new QLabel(tr("Blog profile name: "), page);
    QLineEdit *nameInput = new QLineEdit(page);
    nameInput->setMaximumWidth(150);
    profileNameLabel->setBuddy(nameInput);
    layout->addWidget(profileNameLabel);
    layout->addWidget(nameInput);

    return page;
}
