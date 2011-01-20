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

#include <QString>
#include <QSettings>

#include "appcontext.h"
#include "mainwindow.h"
#include "qtsingleapplication.h"

using namespace orbitswriter;

int main(int argc, char *argv[])
{
    QtSingleApplication app(argc, argv);
    app.setOrganizationName("Galaxy");
    app.setApplicationName("OrbitsWriter");
    app.setApplicationVersion("0.0.1");
    app.addLibraryPath("./plugins");

    QString message;
    for(int i = 1; i < argc; ++i) {
        message += argv[i];
        if(i < argc - 1) {
            message += ";";
        }
    }
    if(app.sendMessage(message)) {
        return 0;
    }

//    AppContext::instance()->loadData();
    MainWindow w;
    w.showMaximized();
    app.setActivationWindow(&w);

    QObject::connect(&app, SIGNAL(messageReceived(QString)),
                     &w, SLOT(activeWindow(QString)));

    return app.exec();
}
