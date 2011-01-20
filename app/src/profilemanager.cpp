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

void ProfileManager::saveBlogProfile(const BlogProfile & profile) const
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("profile");
    if(!db.open()) {
        QMessageBox::critical(0, QObject::tr("Database Error"), QObject::tr("Can not open profile database."));
        return;
    }
    QSqlQuery query;
    query.exec("select count(*) from sqlite_master where name='blog_profile'");
    if(query.next()) {
        if(query.value(0).toInt() == 0) {
            // no such table named blog_profile
            // create this table
            query.exec("CREATE TABLE blog_profile ("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "name VARCHAR(100), "
                       "addr VARCHAR(100), "
                       "user_name VARCHAR(50), "
                       "password VARCHAR(50), "
                       "type VARCHAR(20), "
                       "publish_url VARCHAR(100))");
        }
    }
    // blog_profile exists
    query.exec(QString("INSERT INTO blog_profile VALUES (null, '%1', '%2', '%3', '%4', '%5', '%6')")
               .arg(profile.profileName, profile.blogAddr, profile.userName, profile.password, profile.blogType, profile.publishUrl));
}
