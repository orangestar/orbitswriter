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
#include "blogprofileconfigwizard.h"
#include "common.h"

using namespace orbitswriter;

BlogProfileDialog::BlogProfileDialog(QWidget *parent) :
    QDialog(parent),
    _shouldReload(false)
{
    blogProfileListWidget = new QListWidget(this);
    QList<BlogProfile *> bpList = ProfileManager::instance()->blogProfileList();
    BlogProfile *bp = NULL;
    foreach(bp, bpList) {
        QListWidgetItem *item = new QListWidgetItem(bp->isDefault
                                                    ? (bp->profileName + Constants::DefaultFlagString)
                                                    : bp->profileName);
        QVariant var;
        var.setValue(*bp);
        item->setData(Qt::UserRole, var);
        blogProfileListWidget->addItem(item);
    }
    QLabel *listLabel = new QLabel(tr("Existing Blog Profiles"), this);

    addButton = new QPushButton(tr("&Add..."), this);
    modButton = new QPushButton(tr("&Modify..."), this);
    delButton = new QPushButton(tr("&Remove"), this);

    buttonBox = new QDialogButtonBox(Qt::Vertical, this);
    buttonBox->addButton(addButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(modButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(delButton, QDialogButtonBox::ActionRole);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

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
    if(button == addButton) {
        addBlogProfile();
    } else if(button == modButton) {
        listDoubleClicked(blogProfileListWidget->currentItem());
    } else if(button == delButton) {
        delBlogProfile();
    } else if(button == buttonBox->button(QDialogButtonBox::Ok)) {
        save();
        QDialog::reject();
    } else if(button == buttonBox->button(QDialogButtonBox::Cancel)) {
        QDialog::reject();
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
        _shouldReload = true;
        BlogProfile profile = w.blogProfile();
        QListWidgetItem *item = new QListWidgetItem;
        if(profile.isDefault) {
            QList<QListWidgetItem *> finds = blogProfileListWidget->findItems(Constants::DefaultFlagString, Qt::MatchEndsWith);
            if(finds.size() == 1) {
                QListWidgetItem *old = finds.at(0);
                old->setText(old->text().left(old->text().lastIndexOf(Constants::DefaultFlagString)));
            }
            item->setText(profile.profileName + Constants::DefaultFlagString);
        } else {
            item->setText(profile.profileName);
        }
        QVariant var;
        var.setValue(profile);
        item->setData(Qt::UserRole, var);
        blogProfileListWidget->addItem(item);
    }
}

void BlogProfileDialog::delBlogProfile()
{

}

void BlogProfileDialog::modifyBlogProfile(BlogProfile & profile)
{

}

void BlogProfileDialog::save()
{

}
