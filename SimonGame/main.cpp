#include "mainwindow.h"
#include "simon.h"

#include <QApplication>

/*
 * Kevin Soto(GitHub username: KevinSotoMiranda) and Markus Buckwalter(GitHub username: markusbuck)
 *
 * https://github.com/UofU-CS3505/cs3505-assignment6-Qt
 *
 * The creative element that we decided on was creating a hard mode. In the hard mode, the
 * red and blue buttons will randomly move to a different location when the bot is pressing a button.
 * The player will have to remember the sequence of patterns, but face the challenge of the the
 * buttons randomly moving around when the bot is pressing the buttons.
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Simon simon;
    MainWindow w(simon);
    w.show();
    return a.exec();
}
