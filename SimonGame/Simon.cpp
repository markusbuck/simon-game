#include "simon.h"
#include <iostream>

Simon::Simon(QObject * parent) : QObject(parent) {
}

void Simon::generateNextPattern() {
    this->playerPatternCounter = 0;

    int randNum = std::rand() % 100;

    if(randNum >= 51) {
        this->botPattern.append("R");
    }

    else {
        this->botPattern.append("B");
    }

    displayBotPattern();
}

void Simon::displayBotPattern(){
    std::cout << "in bot" << std::endl;
    for(int i = 0; i < this->botPattern.length(); i ++){
        QTimer::singleShot(400 * (i + 1), this, [this, i]{emit lightBotButton(this->botPattern.at(i));});
    }

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
    this->botPattern = "";
    this->playerPattern = "";
    this->playerPatternCounter = 0;
}

void Simon::startGame(){
    isGameStart = true;
    generateNextPattern();
    emit toggleStart(false);
    emit toggleButtons(true);
}

void Simon::startHardGame(){
    isGameStart = true;
    generateNextPattern();
    emit toggleStart(false);
    emit toggleHard(false);
    emit toggleButtons(true);
}

void Simon::addBlueToPlayerPattern() {
    this->playerPattern += "B";
    bool isCorrectPattern = this->isPlayerPatternCorrect();

    if(!isCorrectPattern) {
        // emit showDeathScreen(true);
        // emit toggleButtons(false);
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
    bool isCorrectPattern = this->isPlayerPatternCorrect();

    if(!isCorrectPattern) {
        // emit showDeathScreen(true);
        // emit toggleButtons(false);
    }

    this->playerPatternCounter++;
    int percentage = ((double)this->playerPatternCounter/ this->botPattern.length()) * 100;

    std::cout << isCorrectPattern << std::endl;
    std::cout << this->playerPattern << std::endl;
    std::cout << "Percentage: " << percentage << std::endl;

    emit incrementProgressBar(percentage);
}
