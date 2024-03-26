#ifndef SIMON_H
#define SIMON_H
#include <QObject>
#include <QTimer>
#include <string>

/*!
 * \brief Kevin Soto and Markus Buckwalter
 * CS 3505
 * Assignment 6: QT Simon Game
 *
 * This class is the representation of a Simon game where a
 * pattern will be randomly generated, and methods to check if the pattern is correct.
 */
class Simon : public QObject {
    Q_OBJECT
private:
    std::string botPattern = "";
    std::string playerPattern = "";
    int playerPatternCounter = 0;
    bool hardMode = false;

public slots:
    /*!
     * \brief The startGame method will generate a pattern of length 1, and will
     * emit signals to disable the start buttons. It will also display the bots moves by giving visual feedback.
     */
    void startGame();

    /*!
     * \brief The startHardGame method will generate a pattern of length 1, and will emit
     * signals to disable the start buttons. It will randomly pick a location for the red, and blue button,
     * and will display the bots moves.
     */
    void startHardGame();

    /*!
     * \brief The addBlueToPlayerPattern method will add a 'B' to the
     * players string to represent that they pressed the blue button.
     */
    void addBlueToPlayerPattern();

    /*!
     * \brief The addRedToPlayerPattern method will add a "R' to the
     * players string to represent that they pressed the red button.
     */
    void addRedToPlayerPattern();


signals:
    /*!
     * \brief The toggleStart will emit a signal to toggle the startbutton
     * when the game has started.
     */
    void toggleStart(bool);

    /*!
     * \brief The toggleHard will emit a signal to toggle the
     * hard mode when the game has started.
     */
    void toggleHard(bool);

    /*!
     * \brief The toggleButtons will emit a signal to toggle the
     * red and blue buttons.
     */
    void toggleButtons(bool);

    /*!
     * \brief The showDeathScreen will emit a signal to toggle the death screen
     * display when the user has inputed the incorrect simon pattern.
     */
    void showDeathScreen(bool);

    /*!
     * \brief The incrementProgressBar will emit a signal to update the progress
     * bar when the user has correctly pressed the correct buttons.
     */
    void incrementProgressBar(int);

    /*!
     * \brief The lightBotButton will emit a signal to give a visual feedback of the bot pressing buttons by changing the color.
     */
    void lightBotButton(char);

    /*!
     * \brief The turnOffBotButton will emit a signal to change the bots pressed button to the original color.
     */
    void turnOffBotButton(char);

    /*!
     * \brief The startAnimation will emit a signal to change the red and blue buttons locations to a random location.
     */
    void startAnimation(int);

    /*!
     * \brief The resetWindow will emit a signal to re enable the start button, and hard mode button so the user can press them.
     */
    void resetWindow(bool);

    /*!
     * \brief The resetButtonLocation will emit a signal to change the red and blue buttons location to its original spot.
     */
    void resetButtonLocation();

public:
    /*!
     * \brief A timer to create delays of the bot button presses, and display how long the death screen is.
     */
    QTimer *timer;
    /*!
     * \brief Simon constructor that will set the QObject pointer to null
     * \param parent: A nullpointer
     */
    explicit Simon(QObject * parent = nullptr);

    /*!
     * \brief The generateNextPattern method will randomly add 'B' or 'R' to the pattern.
     */
    void generateNextPattern();

    /*!
     * \brief the displayBotPattern method will emit signals to show the bot pressing the red and blue buttons.
     */
    void displayBotPattern();

    /*!
     * \brief The isPlayerPatternCorrect method will check if the players pattern is correct compared to the bots pattern.
     * \return True if the pattern is correct, false otherwise.
     */
    bool isPlayerPatternCorrect();

    /*!
     * \brief The resetGame method will reset the player counter, bots, and players pattern, and will toggle the blue and red buttons so they are not clickable.
     */
    void resetGame();
};

#endif // SIMON_H
