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

#ifndef DBWORKER_H
#define DBWORKER_H

class QString;

namespace orbitswriter
{

struct BlogProfile;

class DBWorker
{
public:
    virtual ~DBWorker() {}

    /*!
       \brief Opens a database named \a databaseName, error message will be save in \a errorMessage.

       If database opens successfully, return true; otherwise false. The error message will be stored
       in \a errorMessage. If database is not exists, a new one should be created.

       \param databaseName database name
       \param errorMessage error message string
       \return true if database opened successfully
     */
    virtual bool open(const QString & databaseName, QString * errorMessage = 0) = 0;

    /*!
       \brief Inserts a blog profile into database.
       \param profile blog profile that should be inserted
       \return true if inserts successfully
     */
    virtual bool insertBlogProfile(const BlogProfile & profile) = 0;

}; // end of class DBWorker

} // end of namespace orbitswriter

#endif // DBWORKER_H
