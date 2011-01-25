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

#ifndef BERKELEYDBWORKER_H
#define BERKELEYDBWORKER_H

#include "dbworker.h"

class Db;

namespace orbitswriter
{

/*!
   \class BerkeleyDBWorker
   \brief Database worker of Berkeley DB.
 */

class BerkeleyDBWorker : public DBWorker
{
public:
    BerkeleyDBWorker();
    ~BerkeleyDBWorker();

    bool open(const QString &databaseName, QString * errorMessage = 0);

    bool insertBlogProfile(const BlogProfile &profile);

private:
    Db *blogProfileDB;

}; // end of class BerkeleyDBWorker

} // end of namespace orbitswriter

#endif // BERKELEYDBWORKER_H
