#include "mainwindow.h"
#include "simon.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Simon simon;
    MainWindow w(simon);
    w.show();
    return a.exec();
}
