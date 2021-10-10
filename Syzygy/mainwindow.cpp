#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initTime();
    initPlanetsImage();

    ui->label->setStyleSheet("color: rgb(250, 250, 250, 0)");
    ui->label->setText(QDateTime::currentDateTime().toString("dd:mm:yyyy hh:mm:ss"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initPlanetsImage(){
    QPixmap obj("Image/Planets/earth.png");
    ui->earth->setPixmap(obj.scaled(ui->earth->width(), ui->earth->height()));
    ui->earth->setStyleSheet("background: transparent;");

    obj.load("Image/Planets/jupiter.png");
    ui->jupiter->setPixmap(obj.scaled(ui->jupiter->width(), ui->jupiter->height()));
    ui->jupiter->setStyleSheet("background: transparent;");

    obj.load("Image/Planets/mars.png");
    ui->mars->setPixmap(obj.scaled(ui->mars->width(), ui->mars->height()));
    ui->mars->setStyleSheet("background: transparent;");

    obj.load("Image/Planets/mercury.png");
    ui->mercury->setPixmap(obj.scaled(ui->mercury->width(), ui->mercury->height()));
    ui->mercury->setStyleSheet("background: transparent;");

    obj.load("Image/Planets/neptune.png");
    ui->neptune->setPixmap(obj.scaled(ui->neptune->width(), ui->neptune->height()));
    ui->neptune->setStyleSheet("background: transparent;");

    obj.load("Image/Planets/saturn.png");
    ui->saturn->setPixmap(obj.scaled(ui->saturn->width(), ui->saturn->height()));
    ui->saturn->setStyleSheet("background: transparent;");

    obj.load("Image/Planets/sun.png");
    ui->sun->setPixmap(obj.scaled(ui->sun->width(), ui->sun->height()));
    ui->sun->setStyleSheet("background: transparent;");

    obj.load("Image/Planets/uranus.png");
    ui->uranus->setPixmap(obj.scaled(ui->uranus->width(), ui->uranus->height()));
    ui->uranus->setStyleSheet("background: transparent;");

    obj.load("Image/Planets/venus.png");
    ui->venus->setPixmap(obj.scaled(ui->venus->width(), ui->venus->height()));
    ui->venus->setStyleSheet("background: transparent;");
}
void MainWindow::initTime(){
    ui->LCDdayAndMonth->display(QDateTime::currentDateTime().toString("dd.MM"));
    ui->LCDdayAndMonth->setStyleSheet("background: transparent;");

    ui->LCDYear->display(QDateTime::currentDateTime().toString(".yyyy"));
    ui->LCDYear->setStyleSheet("background: transparent;");

    ui->LCDTime->display(QDateTime::currentDateTime().toString("hh:mm"));
    ui->LCDTime->setStyleSheet("background: transparent;");

}
