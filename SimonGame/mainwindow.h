#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include "simon.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void updateProgressBar();
    void lightUpButton(char);
    void startAnimation();
signals:
    void resetProgressBar();
    void restartAnimation();

public:
    MainWindow(Simon& simon, QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

    QPropertyAnimation *blueAnimation;
    QPropertyAnimation *redAnimation;
};
#endif // MAINWINDOW_H
