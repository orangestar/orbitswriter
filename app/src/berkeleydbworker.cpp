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

#include "db_cxx.h"

using namespace orbitswriter;

BerkeleyDBWorker::BerkeleyDBWorker()
    : blogProfileDB(new Db(NULL, 0))
{
}

BerkeleyDBWorker::~BerkeleyDBWorker()
{
    delete blogProfileDB;
}

bool BerkeleyDBWorker::open(const QString &databaseName, QString * errorMessage /* = 0 */)
{
    try {
        return (blogProfileDB->open(NULL, databaseName.toLatin1().constData(), NULL, DB_RECNO, DB_CREATE, 0) == 0);
    } catch(DbException &e) {
        errorMessage = new QString(e.what());
        return false;
    } catch(std::exception &e) {
        errorMessage = new QString(e.what());
        return false;
    }
}

bool BerkeleyDBWorker::close(QString *errorMessage)
{
    try {
        return (blogProfileDB->close(0) == 0);
    } catch(DbException &e) {
        errorMessage = new QString(e.what());
        return false;
    } catch(std::exception &e) {
        errorMessage = new QString(e.what());
        return false;
    }
}

bool BerkeleyDBWorker::insertBlogProfile(const BlogProfile &profile, QString * errorMessage /* = 0 */)
{
    DBT key, data;

    return false;
}
