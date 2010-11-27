#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Galaxy");
    app.setApplicationName("OrbitsWriter");
    app.setApplicationVersion("0.0.1");

    MainWindow w;
    w.showMaximized();

    return app.exec();
}
