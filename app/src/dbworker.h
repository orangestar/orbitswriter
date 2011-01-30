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

#include <QString>

#include "dbworker.h"

#ifdef BERKELEYDB
class Db;
#endif

namespace orbitswriter
{

/*!
   \struct BlogProfile
   \brief Blog profile data.
 */
struct BlogProfile
{
    /*!
       \brief Blog address. This is the address browsers access with.
     */
    QString blogAddr;

    /*!
       \brief User name of blog login.
     */
    QString userName;

    /*!
       \brief Password of blog login.
     */
    QString password;

    /*!
       \brief Whether password should be remembered or not.
     */
    bool rememberPassword;

    /*!
       \brief Blog API type.
     */
    QString blogType;

    /*!
       \brief Remote publish URL of this blog.
     */
    QString publishUrl;

    /*!
       \brief Name of this profile.
     */
    QString profileName;

    /*!
       \brief As default account.
     */
    bool isDefault;
};

/*!
   \class DBWorker
   \brief Business database interface.

   This is an interface for all database operations used in OrbitsWriter. Note that
   each function only need to do what described in the comments. For example,
   function that inserts data need not to check if the database is opened first.
 */

class DBWorker
{
public:
    virtual ~DBWorker() {}

    /*!
       \brief Opens a database named \a databaseName, error message will be saved in \a errorMessage.

       If database opens successfully, return true; otherwise false. The error message will be stored
       in \a errorMessage. If database is not exists, a new one should be created.

       \param databaseName database name
       \param errorMessage error message string
       \return true if database opened successfully
     */
    virtual bool open(const QString & databaseName, QString * errorMessage = 0) = 0;

    /*!
       \brief Inserts a blog profile \a profile into profile database,
       error message will be saved in \a errorMessage.

       If inserts successfully, return true; otherwise false. The error message will be stored
       in \a errorMessage.

       \param profile blog profile that should be inserted
       \param errorMessage error message string
       \return true if inserts successfully
     */
    virtual bool insertBlogProfile(const BlogProfile & profile, QString * errorMessage = 0) = 0;

    /*!
       \brief Closes the database, error message will be saved in \a errorMessage.

       If database closes successfully, return true; otherwise false. The error message will be stored
       in \a errorMessage.

       \param errorMessage error message string
       \return true if database closed successfully
     */
    virtual bool close(QString * errorMessage = 0) = 0;

}; // end of class DBWorker

#ifdef BERKELEYDB

/*!
   \class BerkeleyDBWorker
   \brief Database operations of Berkeley DB.
 */

class BerkeleyDBWorker : public DBWorker
{
public:
    BerkeleyDBWorker();
    ~BerkeleyDBWorker();

    bool open(const QString &databaseName, QString * errorMessage = 0);

    bool close(QString * errorMessage = 0);

    bool insertBlogProfile(const BlogProfile &profile, QString * errorMessage = 0);

private:
    Db *blogProfileDB;

}; // end of class BerkeleyDBWorker

#endif

} // end of namespace orbitswriter

#endif // DBWORKER_H
