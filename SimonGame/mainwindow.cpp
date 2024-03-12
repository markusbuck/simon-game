#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simon.h"

MainWindow::MainWindow(Simon& simon, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Disable start button when pressed
    connect(ui->startButton,
            &QPushButton::clicked,
            &simon,
            &Simon::startGame);
    connect(&simon,
            &Simon::toggleStart,
            ui->startButton,
            &QPushButton::setEnabled);

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

    // QTimer::singleShot(200, this, &foo::slotA);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateProgressBar() {
    int maxVal = ui->progressBar->maximum();
    int currentVal = ui->progressBar->value();

    if(currentVal == maxVal) {
        ui->progressBar->setValue(0);
        emit resetProgressBar();
    }
}
