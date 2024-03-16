#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simon.h"
#include <iostream>

MainWindow::MainWindow(Simon& simon, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->deathText->setVisible(false);

    blueAnimation = new QPropertyAnimation(ui->blueButton, "geometry");
    redAnimation = new QPropertyAnimation(ui->redButton, "geometry");

    // Disable start button when pressed
    connect(ui->startButton,
            &QPushButton::clicked,
            &simon,
            &Simon::startGame);

    connect(&simon,
            &Simon::toggleStart,
            ui->startButton,
            &QPushButton::setEnabled);

    connect(ui->hardButton,
            &QPushButton::clicked,
            &simon,
            &Simon::startHardGame);

    connect(&simon,
            &Simon::toggleHard,
            ui->hardButton,
            &QPushButton::setEnabled);

    connect(&simon,
            &Simon::startAnimation,
            this,
            &MainWindow::startAnimation);

    // Enable blue and red buttons
    connect(&simon,
            &Simon::toggleButtons,
            ui->redButton,
            &QPushButton::setEnabled);

    connect(&simon,
            &Simon::toggleButtons,
            ui->blueButton,
            &QPushButton::setEnabled);

    ui->redButton->setStyleSheet(
        QString("QPushButton {background-color: "
                "rgb(200,50,50);} QPushButton:pressed {background-color: "
                "rgb(255,150,150);}"));

    ui->blueButton->setStyleSheet(
        QString("QPushButton {background-color: "
                "rgb(50,50,200);} QPushButton:pressed {background-color: "
                "rgb(150,150,255);}"));

    connect(&simon,
            &Simon::incrementProgressBar,
            ui->progressBar,
            &QProgressBar::setValue);

    connect(ui->progressBar,
            &QProgressBar::valueChanged,
            this,
            &MainWindow::updateProgressBar);

    // Reset progress bar if player was correct
    connect(this,
            &MainWindow::resetProgressBar,
            &simon,
            &Simon::generateNextPattern);

    connect(&simon,
            &Simon::lightBotButton,
            this,
            &MainWindow::lightUpButton);

    connect(&simon,
            &Simon::turnOffBotButton,
            this,
            &MainWindow::turnOffButton);

    connect(ui->blueButton,
            &QPushButton::clicked,
            &simon,
            &Simon::addBlueToPlayerPattern);

    connect(ui->redButton,
            &QPushButton::clicked,
            &simon,
            &Simon::addRedToPlayerPattern);

    connect(&simon,
            &Simon::showDeathScreen,
            ui->deathText,
            &QTextBrowser::setVisible);

    connect(&simon,
            &Simon::resetWindow,
            this,
            &MainWindow::resetWindow);

    connect(&simon,
            &Simon::resetButtonLocation,
            this,
            &MainWindow::resetButtonsLocation);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetButtonsLocation(){
    ui->redButton->move(60, 70);
    ui->blueButton->move(410,70);
}

void MainWindow::updateProgressBar() {
    int maxVal = ui->progressBar->maximum();
    int currentVal = ui->progressBar->value();

    if(currentVal == maxVal) {
        emit resetProgressBar();
        // emit restartAnimation();
    }
}

void MainWindow::lightUpButton(char buttonLetter){
    if(buttonLetter == 'R'){
        ui->redButton->setStyleSheet(
            QString("QPushButton {background-color: "
                    "rgb(255,150,150);}"));

    }else if(buttonLetter == 'B'){
        ui->blueButton->setStyleSheet(
            QString("QPushButton {background-color: "
                    "rgb(150,150,255);}"));
    }
}

void MainWindow::turnOffButton(char buttonLetter){
    if(buttonLetter == 'B'){
        ui->blueButton->setStyleSheet(
            QString("QPushButton {background-color: "
                    "rgb(50,50,200);} QPushButton:pressed {background-color: "
                    "rgb(150,150,255);}"));

    }else if(buttonLetter == 'R'){
        ui->redButton->setStyleSheet(
            QString("QPushButton {background-color: "
                    "rgb(200,50,50);} QPushButton:pressed {background-color: "
                    "rgb(255,150,150);}"));
    }
}

void MainWindow::startAnimation(int time){
    std::cout << "Animating" << std::endl;
    blueAnimation ->setDuration(time);
    blueAnimation->setStartValue(ui->blueButton->geometry());
    int randBlueX = arc4random() % 500;
    int randBlueY = arc4random() % 300;
    blueAnimation->setEndValue(QRect(randBlueX, randBlueY, ui->blueButton->width(), ui->blueButton->height()));
    blueAnimation->start();

    redAnimation ->setDuration(time);
    redAnimation->setStartValue(ui->redButton->geometry());
    int randRedX = arc4random() % 500;
    int randRedY = arc4random() % 300;
    redAnimation->setEndValue(QRect(randRedX, randRedY, ui->redButton->width(), ui->redButton->height()));
    redAnimation->start();
}

void MainWindow::resetWindow(){
    ui->startButton->setEnabled(true);
    ui->hardButton->setEnabled(true);
}
