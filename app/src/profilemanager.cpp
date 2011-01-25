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

#include "berkeleydbworker.h"

#define DB_BLOG_PROFILE "blog.profile"
#define DB_USER_PROFILE "user.profile"

using namespace orbitswriter;

ProfileManager::ProfileManager()
    : QObject(0),
      db(new BerkeleyDBWorker)
{
}

ProfileManager::~ProfileManager()
{
//    clearBlogProfileList();
}

void ProfileManager::saveBlogProfile(const BlogProfile & profile)
{
//    if(!openProfileDatabase()) {
//        return;
//    }
//    QSqlQuery query;
//    if(!isBlogProfileTableExists()) {
//        // create table
//        query.exec("CREATE TABLE blog_profile ("
//                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
//                   "name VARCHAR(100), "
//                   "addr VARCHAR(100), "
//                   "user_name VARCHAR(50), "
//                   "password VARCHAR(50), "
//                   "type VARCHAR(20), "
//                   "publish_url VARCHAR(100), "
//                   "is_default TINYINT)");
//    }
//    if(profile.isDefault) {
//        query.exec("UPDATE blog_profile SET is_default = 0");
//    }
//    // blog_profile exists
//    query.exec(QString("INSERT INTO blog_profile VALUES (null, '%1', '%2', '%3', '%4', '%5', '%6', %7)")
//               .arg(profile.profileName,
//                    profile.blogAddr,
//                    profile.userName,
//                    profile.rememberPassword ? profile.password : "",
//                    profile.blogType,
//                    profile.publishUrl,
//                    profile.isDefault ? "1" : "0"));
//    closeConnection();
//    emit blogProfileCreated();
}

QList<BlogProfile *> & ProfileManager::blogProfileList()
{
    QString err;
    if(db->open(QString(DB_BLOG_PROFILE), &err)) {
        qDebug() << "opened";
    } else {
        QMessageBox::critical(0, tr("Database Error"), tr("Can not open profile database. Error message: \n%1").arg(err));
    }
//    if(_blogProfileList.isEmpty()) {
//        clearBlogProfileList();
//    }
//    if(openProfileDatabase() && isBlogProfileTableExists()) {
//        QSqlQuery query("SELECT * FROM blog_profile");
//        while(query.next()) {
//            BlogProfile *profile = new BlogProfile;
//            QSqlRecord record = query.record();
//            int idx = record.indexOf("name");
//            profile->profileName = query.value(idx).toString();
//            idx = record.indexOf("addr");
//            profile->blogAddr = query.value(idx).toString();
//            idx = record.indexOf("user_name");
//            profile->userName = query.value(idx).toString();
//            idx = record.indexOf("password");
//            profile->password = query.value(idx).toString();
//            profile->rememberPassword = !profile->password.isEmpty();
//            idx = record.indexOf("type");
//            profile->blogType = query.value(idx).toString();
//            idx = record.indexOf("publish_url");
//            profile->publishUrl = query.value(idx).toString();
//            idx = record.indexOf("is_default");
//            profile->isDefault = query.value(idx).toInt() == 1;
//            _blogProfileList.append(profile);
//        }
//        closeConnection();
//    }
    return _blogProfileList;
}

bool ProfileManager::openProfileDatabase()
{
    QSqlDatabase db = QSqlDatabase::database(QSqlDatabase::defaultConnection);
    if(!db.isValid()) {
        db = QSqlDatabase::addDatabase("QSQLITE", QSqlDatabase::defaultConnection);
    }
    db.setDatabaseName("profile");
    if(!db.open()) {
        QMessageBox::critical(0, tr("Database Error"), tr("Can not open profile database."));
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

void ProfileManager::closeConnection()
{
    QSqlDatabase db = QSqlDatabase::database(QSqlDatabase::defaultConnection);
    if(db.isValid()) {
        db.close();
    }
}

void ProfileManager::clearBlogProfileList()
{
    qDeleteAll(_blogProfileList.begin(), _blogProfileList.end());
    _blogProfileList.clear();
}
