#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    Thread mThread1;
//    mThread1.name = "mThread1";
//    mThread1.start();

    w.show();
    return a.exec();
}
