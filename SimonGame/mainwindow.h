#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include "simon.h"

QT_BEGIN_NAMESPACE
namespace Ui {
/*! Kevin Soto and Markus Buckwalter
 * CS 3505 Assignment 6: QT Simon Game
 *
 * This class is the controller and view of the Simon Game.
 */
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    /*!
     * \brief The updateProgressBar method will update the percentage of moves the player has completed.
     */
    void updateProgressBar();

    /*!
     * \brief The lightUpButton method will change the red, and blue buttons color to represent a button press.
     */
    void lightUpButton(char);

    /*!
     * \brief The turnOffButton method will change the red, and blue buttons color back to its
     * original one to represent the button has finished being pressed.
     */
    void turnOffButton(char);

    /*!
     * \brief The startAnimation method will randomly move the red and blue buttons location.
     */
    void startAnimation(int);

    /*!
     * \brief The resetWindow method will enable the start and hard mode buttons so the user can press them.
     */
    void resetWindow();

    /*!
     * \brief The resetButtonsLocation method will reset the red and blue buttons location back to its original spot.
     */
    void resetButtonsLocation();

signals:
    /*!
     * \brief The resetProgressBar will emit a signal to change the progress bars value to zero.
     */
    void resetProgressBar();

public:
    /*!
     * \brief MainWindow constructor that takes in a Simon, and QWidget object.
     * \param simon: The object representing the simon game.
     * \param parent: A nullpointer.
     */
    MainWindow(Simon& simon, QWidget *parent = nullptr);

    /*
     * A destructor to remove any newly created allocated data.
     */
    ~MainWindow();
private:
    Ui::MainWindow *ui;

    QPropertyAnimation *blueAnimation;
    QPropertyAnimation *redAnimation;
};
#endif // MAINWINDOW_H
