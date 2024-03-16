#ifndef SIMON_H
#define SIMON_H
#include <QObject>
#include <QTimer>
#include <string>


class Simon : public QObject {
    Q_OBJECT
private:
    std::string botPattern = "";
    std::string playerPattern = "";
    int playerPatternCounter = 0;
    bool hardMode = false;

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
    void turnOffBotButton(char);
    void startAnimation(int);
    void resetWindow(bool);
    void resetButtonLocation();

public:
    QTimer *timer;
    explicit Simon(QObject * parent = nullptr);
    void generateNextPattern();
    void displayBotPattern();
    bool isPlayerPatternCorrect();
    void resetGame();
};

#endif // SIMON_H
