#include "simon.h"
#include <iostream>

Simon::Simon(QObject * parent) : QObject(parent) {
}

void Simon::generateNextPattern() {
    QTimer::singleShot((200), this, [this]{emit incrementProgressBar(0);});

    this->playerPatternCounter = 0;

    int randNum = arc4random() % 100;

    if(randNum >= 51) {
        this->botPattern.append("R");
    }

    else {
        this->botPattern.append("B");
    }

    emit toggleButtons(false);
    displayBotPattern();
}

void Simon::displayBotPattern(){
    std::cout << "in bot" << std::endl;
    int timer = 400;
    int totalTime = 0;
    for(int i = 0; i < this->botPattern.length(); i ++){
        std::cout << this->botPattern.at(i) << std::endl;
        totalTime = timer + 400;

        QTimer::singleShot(timer, this, [this, i]{emit lightBotButton(this->botPattern.at(i));});
        QTimer::singleShot((timer + 400), this, [this, i]{emit turnOffBotButton(this->botPattern.at(i));});
        if(this->botPattern.length() <= 400){
            timer += (1000 - this->botPattern.length());
        }else
            timer += timer;
    }
    if(hardMode){
        emit startAnimation(totalTime);
    }
    this->playerPattern = "";
    QTimer::singleShot((totalTime), this, [this]{emit toggleButtons(true);});
}

bool Simon::isPlayerPatternCorrect() {
    if(this->playerPattern.length() > this->botPattern.length()) {
        return false;
    }

    for(int i = 0; i < this->playerPattern.length(); i++) {
        if(this->playerPattern.at(i) != this->botPattern.at(i)) {
            return false;
        }
    }
    return true;
}

void Simon::resetGame() {
    hardMode = false;

    emit showDeathScreen(true);
    emit toggleButtons(false);
    emit resetButtonLocation();

    QTimer::singleShot((1000), this, [this]{emit showDeathScreen(false);});
    QTimer::singleShot((1200), this, [this]{emit resetWindow(true);});

    this->botPattern = "";
    this->playerPattern = "";
    this->playerPatternCounter = 0;
}

void Simon::startGame(){
    generateNextPattern();
    emit toggleStart(false);
    emit toggleHard(false);
}

void Simon::startHardGame(){
    hardMode = true;
    generateNextPattern();
    emit toggleStart(false);
    emit toggleHard(false);
    emit startAnimation(400);
}

void Simon::addBlueToPlayerPattern() {
    this->playerPattern += "B";
    bool isCorrectPattern = this->isPlayerPatternCorrect();

    if(!isCorrectPattern) {
        resetGame();

        return;
    }

    this->playerPatternCounter++;

    int percentage = ((double)this->playerPatternCounter/ this->botPattern.length()) * 100;
    std::cout << isCorrectPattern << std::endl;
    std::cout << this->playerPattern << std::endl;
    std::cout << "Percentage: "  << percentage << std::endl;

    emit incrementProgressBar(percentage);

}

void Simon::addRedToPlayerPattern() {
    this->playerPattern += "R";
    std::cout << this->playerPattern << std::endl;
    bool isCorrectPattern = this->isPlayerPatternCorrect();

    if(!isCorrectPattern) {
        resetGame();

        return;
    }
    this->playerPatternCounter++;
    int percentage = ((double)this->playerPatternCounter/ this->botPattern.length()) * 100;

    std::cout << isCorrectPattern << std::endl;
    std::cout << this->playerPattern << std::endl;
    std::cout << "Percentage: " << percentage << std::endl;

    emit incrementProgressBar(percentage);
}
