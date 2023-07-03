#include "Widgets/MainWindow.h"
#include <QApplication>
#include <iostream>
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow mainwindow;
    mainwindow.show();

    return app.exec();
}
