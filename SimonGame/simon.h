#ifndef SIMON_H
#define SIMON_H
#include <QObject>
#include <string>


class Simon : public QObject {
    Q_OBJECT
private:
    std::string pattern = "";

public slots:
    bool isPlayerPatternCorrect(std::string pattern);
    void startGame();

signals:
    void toggleStart(bool);

public:
    explicit Simon(QObject * parent = nullptr);
    void generateNextPattern();
    void resetPattern();
    bool isGameOver = false;
    bool isGameStart = false;
    bool playersTurn = false;
};

#endif // SIMON_H
