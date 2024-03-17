#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simon.h"
#include <QRandomGenerator>

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

    // Disable hard mode when pressed
    connect(ui->hardButton,
            &QPushButton::clicked,
            &simon,
            &Simon::startHardGame);

    connect(&simon,
            &Simon::toggleHard,
            ui->hardButton,
            &QPushButton::setEnabled);

    // Move the red and blue buttons to a random location
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

    // Make the redButtons color red
    ui->redButton->setStyleSheet(
        QString("QPushButton {background-color: "
                "rgb(200,50,50);} QPushButton:pressed {background-color: "
                "rgb(255,150,150);}"));

    // Make the blueButtons color to blue
    ui->blueButton->setStyleSheet(
        QString("QPushButton {background-color: "
                "rgb(50,50,200);} QPushButton:pressed {background-color: "
                "rgb(150,150,255);}"));

    // Change the progress bars percentage
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

    // Display the bot pressing buttons
    connect(&simon,
            &Simon::lightBotButton,
            this,
            &MainWindow::lightUpButton);

    connect(&simon,
            &Simon::turnOffBotButton,
            this,
            &MainWindow::turnOffButton);

    // Add 'B' to the players input
    connect(ui->blueButton,
            &QPushButton::clicked,
            &simon,
            &Simon::addBlueToPlayerPattern);

    // Add 'R' to the players input
    connect(ui->redButton,
            &QPushButton::clicked,
            &simon,
            &Simon::addRedToPlayerPattern);

    // Show the death screen if the player lost
    connect(&simon,
            &Simon::showDeathScreen,
            ui->deathText,
            &QTextBrowser::setVisible);

    // Reset the game modes, and button locations
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
    blueAnimation ->setDuration(time);
    blueAnimation->setStartValue(ui->blueButton->geometry());
    int randBlueX = QRandomGenerator::global()->bounded(500);
    int randBlueY = QRandomGenerator::global()->bounded(300);
    blueAnimation->setEndValue(QRect(randBlueX, randBlueY, ui->blueButton->width(), ui->blueButton->height()));
    blueAnimation->start();

    redAnimation ->setDuration(time);
    redAnimation->setStartValue(ui->redButton->geometry());
    int randRedX = QRandomGenerator::global()->bounded(500);
    int randRedY = QRandomGenerator::global()->bounded(300);
    redAnimation->setEndValue(QRect(randRedX, randRedY, ui->redButton->width(), ui->redButton->height()));
    redAnimation->start();
}

void MainWindow::resetWindow(){
    ui->startButton->setEnabled(true);
    ui->hardButton->setEnabled(true);
}
