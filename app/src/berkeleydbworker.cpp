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

#include <QtCore>

#include "dbworker.h"
#include "dataobjs.h"

using namespace orbitswriter;

BerkeleyDBWorker::BerkeleyDBWorker()
    : blogProfileDB(new Db(NULL, 0))
{
}

BerkeleyDBWorker::~BerkeleyDBWorker()
{
    delete blogProfileDB;
    blogProfileDB = 0;
}

bool BerkeleyDBWorker::open(const QString &databaseName, QString & message)
{
    try {
        return blogProfileDB->open(NULL, databaseName.toUtf8().constData(), NULL, DB_HASH, DB_CREATE, 0) == 0;
    } catch(DbException &e) {
        message = e.what();
    } catch(std::exception &e) {
        message = e.what();
    }
    QString msg;
    close(msg);
    return false;
}

bool BerkeleyDBWorker::close(QString & message)
{
    try {
        return blogProfileDB->close(0) == 0;
    } catch(DbException &e) {
        message = e.what();
    } catch(std::exception &e) {
        message = e.what();
    }
    return false;
}

bool BerkeleyDBWorker::insertBlogProfile(const BlogProfile &profile, QString & message)
{
    QByteArray arr = profile.profileName.toUtf8();
    Dbt key((void *)arr.data(), arr.length() + 1);
    Dbt data = createDbt(profile);
    try {
        int ret = blogProfileDB->put(0, &key, &data, DB_NOOVERWRITE);
        if(ret == DB_KEYEXIST) {
            message = QObject::tr("Key %1 already exists.").arg(profile.profileName);
        }
        return ret == 0;
    } catch(DbException &e) {
        message = e.what();
    } catch(std::exception &e) {
        message = e.what();
    }
    return false;
}

bool BerkeleyDBWorker::blogProfileList(QList<BlogProfile *> & list, QString & message)
{
    bool success = false;
    Dbc *cursor = NULL;
    try {
        blogProfileDB->cursor(NULL, &cursor, 0);
        Dbt key;
        Dbt data;
        int ret;
        while((ret = cursor->get(&key, &data, DB_NEXT)) == 0) {
            BlogProfile *p = new BlogProfile;
            p->profileName = QString::fromUtf8((char *)key.get_data());
            QString d = QString::fromUtf8((char *)data.get_data());
            QStringList dl = d.split(DATA_SEPARATOR);
            p->blogAddr = dl.at(0);
            p->userName = dl.at(1);
            p->blogType = dl.at(2);
            p->publishUrl = dl.at(3);
            p->isDefault = false;
            if(dl.size() > 4) {
                p->password = dl.at(4);
            }
            list.append(p);
        }
        success = true;
    } catch(DbException &e) {
        message = e.what();
    } catch(std::exception &e) {
        message = e.what();
    }
    if(cursor != NULL) {
        cursor->close();
    }
    return success;
}

bool BerkeleyDBWorker::deleteBlogProfile(const QString &profileName, QString & message)
{
    QByteArray arr = profileName.toUtf8();
    Dbt key((void *)arr.data(), arr.length() + 1);
    try {
        return blogProfileDB->del(NULL, &key, 0) == 0;
    } catch(DbException &e) {
        message = e.what();
    } catch(std::exception &e) {
        message = e.what();
    }
    return false;
}

Dbt BerkeleyDBWorker::createDbt(const BlogProfile &profile) const
{
    QByteArray arr;
    arr.append(profile.blogAddr.toUtf8()).append(DATA_SEPARATOR)
       .append(profile.userName.toUtf8()).append(DATA_SEPARATOR)
       .append(profile.blogType.toUtf8()).append(DATA_SEPARATOR)
       .append(profile.publishUrl.toUtf8());
    if(profile.rememberPassword) {
        arr.append(DATA_SEPARATOR).append(profile.password.toUtf8());
    }
    return Dbt((void *)arr.data(), arr.length() + 1);
}

const QString BerkeleyDBWorker::DATA_SEPARATOR = QString("*");
