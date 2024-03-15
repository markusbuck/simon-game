#ifndef SIMON_H
#define SIMON_H
#include <QObject>
#include <QTimer>
#include <string>


class Simon : public QObject {
    Q_OBJECT
private:
    std::string botPattern = "";
    int playerPatternCounter = 0;

public slots:
    void startGame();
    void startHardGame();
    void addBlueToPlayerPattern();
    void addRedToPlayerPattern();


signals:
    void toggleStart(bool);
    void toggleHard(bool);
    void toggleButtons(bool);
    void showDeathScreen(bool);
    void incrementProgressBar(int);
    void lightBotButton(char);
    void startAnimation();


public:
    QTimer *timer;
    std::string playerPattern = "";
    explicit Simon(QObject * parent = nullptr);
    void generateNextPattern();
    void displayBotPattern();
    bool isPlayerPatternCorrect();
    void resetGame();
    bool isGameOver = false;
    bool isGameStart = false;
    bool playersTurn = false;
};

#endif // SIMON_H
