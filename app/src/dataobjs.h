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

/*!
   \file dataobjs.h
   \brief There are serveral common data classes defined in this file.

   These common data classes usually without any UI parts.
 */

#ifndef DATAOBJS_H
#define DATAOBJS_H

#include <QString>
#include <QMetaType>

namespace orbitswriter
{

/*!
   \class BlogProfile
   \brief Blog profile data.
 */
class BlogProfile
{
public:
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
}; // end of class BlogProfile

} // end of namespace orbitswriter

Q_DECLARE_METATYPE(orbitswriter::BlogProfile)

#endif // DATAOBJS_H
