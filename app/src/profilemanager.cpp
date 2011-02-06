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

#include "profilemanager.h"
#include "appcontext.h"

#define DB_BLOG_PROFILE "blog_profile.db"
#define DB_USER_PROFILE "user_profile.db"

#ifdef BERKELEYDB
#define CLASS_DBWORKER BerkeleyDBWorker
#endif

using namespace orbitswriter;

ProfileManager::ProfileManager()
    : shouldReload(true)
{
}

ProfileManager::~ProfileManager()
{
    clearBlogProfileList();
}

void ProfileManager::saveBlogProfile(const BlogProfile & profile)
{
    DBWorker *db = new CLASS_DBWORKER;
    if(openProfileDatabase(db)) {
        QString errMsg;
        if(!db->insertBlogProfile(profile, errMsg)) {
            QMessageBox::warning(NULL,
                                 QObject::tr("Insert Failed"),
                                 QObject::tr("Insert blog profile failed. Error message: \n%1").arg(errMsg));
        }
        closeConnection(db);
    }
    delete db;
    if(profile.isDefault) {
        AppContext::instance()->setDefaultBlogProfile(profile.profileName);
    }
    shouldReload = true;
}

QList<BlogProfile *> ProfileManager::blogProfileList()
{
    if(shouldReload) {
        clearBlogProfileList();
        DBWorker *db = new CLASS_DBWORKER;
        if(openProfileDatabase(db)) {
            QString errMsg;
            db->blogProfileList(_blogProfileList, errMsg);
            closeConnection(db);
        }
        delete db;
        QString defaultBlogProfile = AppContext::instance()->defaultBlogProfile();
        BlogProfile *profile;
        foreach(profile, _blogProfileList) {
            if(profile->profileName == defaultBlogProfile) {
                profile->isDefault = true;
            }
        }
        shouldReload = false;
    }
    return _blogProfileList;
}

bool ProfileManager::openProfileDatabase(DBWorker * db)
{
    QString errMsg;
    bool ret = db->open(QString(DB_BLOG_PROFILE), errMsg);
    if(!ret) {
        QMessageBox::critical(NULL,
                              QObject::tr("Database Error"),
                              QObject::tr("Can not open profile database. Error message: \n%1").arg(errMsg));
    }
    return ret;
}

void ProfileManager::closeConnection(DBWorker * db)
{
    QString msg;
    if(!db->close(msg)) {
        QMessageBox::critical(NULL,
                              QObject::tr("Database Error"),
                              QObject::tr("Can not close profile database. Error message: \n%1").arg(msg));
    }
}

void ProfileManager::clearBlogProfileList()
{
    qDeleteAll(_blogProfileList.begin(), _blogProfileList.end());
    _blogProfileList.clear();
}
