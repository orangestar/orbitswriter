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

#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <QFont>

/*!
   \class AppContext
   \brief Application context.
   Application context is usually global data. When application exits,
   context data may need be written into local files.
   This is a singleton class.
 */
class AppContext
{
public:
    /*!
       \brief Gets the only singleton instance.
       \return the pointer to the instance
     */
    inline static AppContext* instance()
    {
        static AppContext ctx;
        return &ctx;
    }

    /*!
       \brief Loads data from local configuration file.
       This file is named by "OrbitsWriter.conf" and is always
       in the same folder of the executable file. If the file does
       not exist or the value is not set, a default value will
       be used in the application.
     */
    void loadData();

    /*!
       \brief Saves data to local configuration file.
       This file is named by "OrbitsWriter.conf" and is always
       in the same folder of the executable file. If the file does
       not exist, a new one will be created.
     */
    void saveData();

    void setDefaultFont(QFont &font)
    {
        _defaultFont = font;
    }

    const QFont& defaultFont() const
    {
        return _defaultFont;
    }

private:
    AppContext();
    ~AppContext() { }
    AppContext(const AppContext &);
    AppContext& operator=(const AppContext &);

    QFont _defaultFont;
};

#endif // APPCONTEXT_H
