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

#include "appcontext.h"

using namespace orbitswriter;

AppContext::AppContext()
    : _defaultFont(QFont("Verdana", 12))
{
}

void AppContext::loadData()
{
    QSettings settings(qApp->applicationDirPath().append("/OrbitsWriter.conf"), QSettings::IniFormat);
    if(settings.contains(DefaultBlogProfile)) {
        // _defaultFont = settings.value(AppContextValue::DEFAULT_FONT).value<QFont>();
        _defaultBlogProfile = settings.value(DefaultBlogProfile).toString();
    }
}

void AppContext::saveData()
{
    QSettings settings(qApp->applicationDirPath().append("/OrbitsWriter.conf"), QSettings::IniFormat);
    settings.setValue(DefaultBlogProfile, _defaultBlogProfile);
}

const QString AppContext::DefaultBlogProfile = QString("Default/BlogProfile");
