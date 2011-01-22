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
#include <QtSql>

#include "profilemanager.h"

using namespace orbitswriter;

ProfileManager::ProfileManager()
{
}

ProfileManager::~ProfileManager()
{
    qDeleteAll(_blogProfileList.begin(), _blogProfileList.end());
    _blogProfileList.clear();
}

void ProfileManager::saveBlogProfile(const BlogProfile & profile)
{
    if(!openProfileDatabase()) {
        return;
    }
    QSqlQuery query;
    if(!isBlogProfileTableExists()) {
        // create table
        query.exec("CREATE TABLE blog_profile ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "name VARCHAR(100), "
                   "addr VARCHAR(100), "
                   "user_name VARCHAR(50), "
                   "password VARCHAR(50), "
                   "type VARCHAR(20), "
                   "publish_url VARCHAR(100))");
    }
    // blog_profile exists
    query.exec(QString("INSERT INTO blog_profile VALUES (null, '%1', '%2', '%3', '%4', '%5', '%6')")
               .arg(profile.profileName,
                    profile.blogAddr,
                    profile.userName,
                    profile.rememberPassword ? profile.password : "",
                    profile.blogType,
                    profile.publishUrl));
}

QList<BlogProfile *> & ProfileManager::blogProfileList()
{
    if(_blogProfileList.isEmpty()) {
        if(openProfileDatabase() && isBlogProfileTableExists()) {
            QSqlQuery query("SELECT * FROM blog_profile");
            while(query.next()) {
                BlogProfile *profile = new BlogProfile;
                QSqlRecord record = query.record();
                int idx = record.indexOf("name");
                profile->profileName = query.value(idx).toString();
                idx = record.indexOf("addr");
                profile->blogAddr = query.value(idx).toString();
                idx = record.indexOf("user_name");
                profile->userName = query.value(idx).toString();
                idx = record.indexOf("password");
                profile->password = query.value(idx).toString();
                profile->rememberPassword = !profile->password.isEmpty();
                idx = record.indexOf("type");
                profile->blogType = query.value(idx).toString();
                idx = record.indexOf("publish_url");
                profile->publishUrl = query.value(idx).toString();
                _blogProfileList.append(profile);
            }
        }
    }
    return _blogProfileList;
}

bool ProfileManager::openProfileDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("profile");
    if(!db.open()) {
        QMessageBox::critical(0, QObject::tr("Database Error"), QObject::tr("Can not open profile database."));
        return false;
    }
    return true;
}

bool ProfileManager::isBlogProfileTableExists()
{
    // NOTE this function will not check if database is opened
    // You should ensure database is opened before this is called
    QSqlQuery query("select count(*) from sqlite_master where name='blog_profile'");
    if(query.next()) {
        return query.value(0).toInt() != 0;
    }
    return false;
}
