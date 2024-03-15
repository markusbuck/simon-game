#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simon.h"
#include <iostream>

MainWindow::MainWindow(Simon& simon, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
            &Simon::toggleHard,
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

    connect(ui->blueButton,
             &QPushButton::clicked,
             &simon,
             &Simon::addBlueToPlayerPattern);

    connect(ui->redButton,
            &QPushButton::clicked,
            &simon,
            &Simon::addRedToPlayerPattern);

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

    connect(this,
            &MainWindow::restartAnimation,
            this,
            &MainWindow::startAnimation);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateProgressBar() {
    int maxVal = ui->progressBar->maximum();
    int currentVal = ui->progressBar->value();

    if(currentVal == maxVal) {
        //ui->progressBar->setValue(0);
        emit resetProgressBar();
        emit restartAnimation();
    }
}

void MainWindow::lightUpButton(char buttonLetter){
    if(buttonLetter == 'R'){
        ui->redButton->setStyleSheet(
            QString("QPushButton {background-color: "
                    "rgb(255,150,150);}"));

        ui->blueButton->setStyleSheet(
            QString("QPushButton {background-color: "
                    "rgb(50,50,200);} QPushButton:pressed {background-color: "
                    "rgb(150,150,255);}"));

    }else if(buttonLetter == 'B'){
        ui->blueButton->setStyleSheet(
            QString("QPushButton {background-color: "
                    "rgb(150,150,255);}"));

        ui->redButton->setStyleSheet(
            QString("QPushButton {background-color: "
                    "rgb(200,50,50);} QPushButton:pressed {background-color: "
                    "rgb(255,150,150);}"));
    }
}

void MainWindow::startAnimation(){
    std::cout << "Animating" << std::endl;
    blueAnimation ->setDuration(1000);
    blueAnimation->setStartValue(ui->blueButton->geometry());
    int randBlueX = std::rand() % 500;
    int randBlueY = std::rand() % 300;
    blueAnimation->setEndValue(QRect(randBlueX, randBlueY, ui->blueButton->width(), ui->blueButton->height()));
    blueAnimation->start();

    redAnimation ->setDuration(1000);
    redAnimation->setStartValue(ui->redButton->geometry());
    int randRedX = std::rand() % 500;
    int randRedY = std::rand() % 300;
    redAnimation->setEndValue(QRect(randRedX, randRedY, ui->redButton->width(), ui->redButton->height()));
    redAnimation->start();
}
