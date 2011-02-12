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
#include <QList>

#ifdef BERKELEYDB
#include "db_cxx.h"
#endif

namespace orbitswriter
{

class BlogProfile;

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
       \brief Opens a database named \a databaseName.

       If database opens successfully, return true; otherwise false.
       The error message will be stored in \a message.
       If the database does not exist, a new one should be created.

       \param databaseName database name
       \param message message string
       \return true if success
     */
    virtual bool open(const QString & databaseName, QString & message) = 0;

    /*!
       \brief Inserts a blog profile \a profile into profile database.

       If inserts successfully, return true; otherwise false.
       The error message will be stored in \a message.

       \param profile blog profile that need to be inserted
       \param message message string
       \return true if success
     */
    virtual bool insertBlogProfile(const BlogProfile & profile, QString & message) = 0;

    /*!
       \brief Closes the database.

       If database closes successfully, return true; otherwise false.
       The error message will be stored in \a message.

       \param message message string
       \return true if success
     */
    virtual bool close(QString & message) = 0;

    /*!
       \brief Gets all saved blog profiles.

       \param list blog profile list to be saved in
       \param message message string
       \return true if success
     */
    virtual bool blogProfileList(QList<BlogProfile *> & list, QString & message) = 0;

    /*!
       \brief Deletes the existing blog profile named \a profileName from database.

       \param profileName profile name
       \param message message string
       \return true if success
     */
    virtual bool deleteBlogProfile(const QString & profileName, QString & message) = 0;

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

    bool open(const QString &databaseName, QString & message);
    bool close(QString & message);
    bool insertBlogProfile(const BlogProfile &profile, QString & message);
    bool blogProfileList(QList<BlogProfile *> & list, QString & message);
    bool deleteBlogProfile(const QString &profileName, QString &message);

private:
    Dbt createDbt(const BlogProfile &profile) const;

    Db *blogProfileDB;

    const static QString DATA_SEPARATOR;
}; // end of class BerkeleyDBWorker

#endif

} // end of namespace orbitswriter

#endif // DBWORKER_H
