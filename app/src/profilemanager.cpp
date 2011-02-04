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

#define DB_BLOG_PROFILE "blog_profile.db"
#define DB_USER_PROFILE "user_profile.db"

#ifdef BERKELEYDB
#define CLASS_DBWORKER BerkeleyDBWorker
#endif

using namespace orbitswriter;

ProfileManager::ProfileManager()
    : QObject(0)
{
}

ProfileManager::~ProfileManager()
{
}

void ProfileManager::saveBlogProfile(const BlogProfile & profile)
{
    DBWorker *db = new CLASS_DBWORKER;
    if(openProfileDatabase(db)) {
        QString errMsg;
        if(!db->insertBlogProfile(profile, errMsg)) {
            QMessageBox::warning(NULL,
                                 tr("Insert Failed"),
                                 tr("Insert blog profile failed. Error message: \n%1").arg(errMsg));
        }
        closeConnection(db);
    }
    delete db;
    emit blogProfileCreated();
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

QList<BlogProfile> ProfileManager::blogProfileList()
{
    DBWorker *db = new CLASS_DBWORKER;
    QList<BlogProfile> list;
    if(openProfileDatabase(db)) {
        QString errMsg;
        db->blogProfileList(list, errMsg);
        closeConnection(db);
    }
    delete db;
    return list;
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
//    return _blogProfileList;
}

bool ProfileManager::openProfileDatabase(DBWorker * db)
{
    QString errMsg;
    bool ret = db->open(QString(DB_BLOG_PROFILE), errMsg);
    if(!ret) {
        QMessageBox::critical(0,
                              tr("Database Error"),
                              tr("Can not open profile database. Error message: \n%1").arg(errMsg));
    }
    return ret;
}

void ProfileManager::closeConnection(DBWorker * db)
{
    QString msg;
    if(!db->close(msg)) {
        QMessageBox::critical(0,
                              tr("Database Error"),
                              tr("Can not close profile database. Error message: \n%1").arg(msg));
    }
}
