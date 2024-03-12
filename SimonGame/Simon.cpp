#include "simon.h"
#include <iostream>

Simon::Simon(QObject * parent) : QObject(parent) {
}

void Simon::generateNextPattern() {
    int randNum = std::rand() % 100;

    if(randNum >= 51) {
        this->pattern.append("R");
    }

    else {
        this->pattern.append("L");
    }
}

bool Simon::isPlayerPatternCorrect(std::string pattern) {
    if(pattern.length() > this->pattern.length()) {
        return false;
    }

    for(int i = 0; i < this->pattern.length(); i++) {
        if(pattern.at(i) != this->pattern.at(i)) {
            return false;
        }
    }

    return true;
}

void Simon::resetPattern() {
    this->pattern = "";
}

void Simon::startGame(){
    isGameStart = true;
    generateNextPattern();
    emit toggleStart(false);
}
