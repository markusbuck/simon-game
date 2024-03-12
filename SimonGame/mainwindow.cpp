#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simon.h"

MainWindow::MainWindow(Simon& simon, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->startButton,
            &QPushButton::clicked,
            &simon,
            &Simon::startGame);
    connect(&simon,
            &Simon::toggleStart,
            ui->startButton,
            &QPushButton::setEnabled);

    ui->redButton->setStyleSheet(
        QString("QPushButton {background-color: "
                "rgb(200,50,50);} QPushButton:pressed {background-color: "
                "rgb(255,150,150);}"));

    ui->blueButton->setStyleSheet(
        QString("QPushButton {background-color: "
                "rgb(50,50,200);} QPushButton:pressed {background-color: "
                "rgb(150,150,255);}"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
