#include <QApplication>

#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("AlarmasABC");
    QCoreApplication::setOrganizationDomain("alarmasabc.net");
    QCoreApplication::setApplicationName("XKHyperCom");

    MainWindow w;
    w.show();

    return app.exec();
}
