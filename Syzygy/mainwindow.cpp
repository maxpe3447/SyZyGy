#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clock = new Clock(ui->LCDdayAndMonth, ui->LCDYear, ui->LCDHourMin, ui->LCDSecond);
    initTime();
    initPlanetsImage();
    initMenuButton();
    ui->groupBox->setStyleSheet("background: transparent;");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete clock;
}
void MainWindow::initPlanetsImage(){

    earth.SetParams(ui->earth, "Image/Planets/earth.png");
    jupiter.SetParams(ui->jupiter, "Image/Planets/jupiter.png");
    mars.SetParams(ui->mars, "Image/Planets/mars.png");
    mercury.SetParams(ui->mercury, "Image/Planets/mercury.png");
    neptune.SetParams(ui->neptune, "Image/Planets/neptune.png");
    saturn.SetParams(ui->saturn, "Image/Planets/saturn.png");
    sun.SetParams(ui->sun, "Image/Planets/sun.png");
    uranus.SetParams(ui->uranus, "Image/Planets/uranus.png");
    venus.SetParams(ui->venus, "Image/Planets/venus.png");

}
void MainWindow::initTime(){

}
void MainWindow::initMenuButton(){
    QPixmap obj("Image/menu.png");
    QIcon ico(obj);
    ui->pbMenu->setIcon(ico);
    ui->pbMenu->setIconSize(ui->pbMenu->size());
}

void MainWindow::on_pbMenu_clicked()
{
    //ui->label->setStyleSheet("color: rgb(255, 255, 255)");
    //ui->label->setText("Yes");
earth.SetPos(100, 100);


}

