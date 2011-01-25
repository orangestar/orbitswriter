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

#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <QObject>
#include <QString>
#include <QList>

namespace orbitswriter
{

class DBWorker;

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
   \class ProfileManager
   \brief Profile manager is the manager of profiles.

   Profiles are used for users and users' blog account. Because profiles may
   contains passwords or other private informations, so these should be stored
   in databases after encrypting.

   Note that profiles are different from application settings. Settings need not
   be encrypted.
 */
class ProfileManager : public QObject
{
    Q_OBJECT
public:
    /*!
       \brief Gets the only singleton instance.
       \return the pointer to the instance
     */
    inline static ProfileManager* instance()
    {
        static ProfileManager mgr;
        return &mgr;
    }

    /*!
       \brief Saves the blog profile.
       \param profile blog profile to be saved
     */
    void saveBlogProfile(const BlogProfile & profile);

    /*!
       \brief Gets blog profile list.
       \return blog profile list read from database
     */
    QList<BlogProfile *> & blogProfileList();

signals:
    void blogProfileCreated();

private:
    bool openProfileDatabase();
    bool isBlogProfileTableExists();
    void closeConnection();
    void clearBlogProfileList();

    ProfileManager();
    ~ProfileManager();
    ProfileManager(const ProfileManager &);
    ProfileManager& operator=(const ProfileManager &);

    DBWorker *db;

    QList<BlogProfile *> _blogProfileList;
}; // end of class ProfileManager

} // end of namespace orbitswriter

#endif // PROFILEMANAGER_H
