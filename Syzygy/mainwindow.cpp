#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), /*isMenuShow{false},*/ isTraveling{false}
{
    ui->setupUi(this);
    ui->groupBox->setStyleSheet("background: transparent; color: rgb(255, 255, 255)");

    infoForm = new PlanetInfoForm();
    aboutProgForm = new AboutProgramForm();
    dvlprsForm = new DevelopersForm();

    clock = new Clock(ui->LCDdayAndMonth, ui->LCDYear, ui->LCDHourMin, ui->LCDSecond, this);
    try {
        dataDB = new DataFromDB();
}  catch(const SyzygyException& ex){
        auto res = SyzygyException::WhatShow(ex);
        switch (res) {
        case QMessageBox::StandardButton::Ok:
            close();
            break;
        case QMessageBox::StandardButton::Cancel:
            ui->statusBar->showMessage("Ok, programm in work");
            break;
        default:
            ui->statusBar->showMessage("Ok, programm in work");
            break;
        }
    }


    initTime();
    initPlanet();
    initPlanetsImage();
    //initMenuButton();

    ui->toolBar->setStyleSheet("background: transparent;"
                               "color: rgb(255, 255, 255)");
    //mngSession.GetLastSession(planets);

    clock->Start();


    connect(ui->aboutProg, &QAction::triggered, this, &MainWindow::on_pbAboutProg_clicked);
    connect(ui->dvlprs, &QAction::triggered, this, &MainWindow::on_dvlprs_clicked);

    travelCursor = QCursor(QPixmap("Image/rocket.png"), 0, 0);
    //algorithms = Algorithms(sun);


    connect(this, &MainWindow::SendOptionsAndInfo, infoForm, &PlanetInfoForm::GetOptionsAndInfo);
}

MainWindow::~MainWindow()
{
    mngSession.SetCurrentSession(planets);

    for(auto planet: planets)
        delete planet;

    delete dataDB;
    delete ui;
    delete clock;
    delete infoForm;
    delete aboutProgForm;
    delete dvlprsForm;
}
void MainWindow::initPlanetsImage(){
    try{
        for(int i = 0; i < planets.size(); i++){
            if(planets[i] != nullptr){

                auto data = dataDB->GetImageOf(planets[i]->GetName(), "cartoon");
                planets[i]->SetParams(data);
            }
        }
    }
    catch(const SyzygyException& ex){
        auto res = SyzygyException::WhatShow(ex);
        switch (res) {
        case QMessageBox::StandardButton::Ok:
            close();
            break;
        case QMessageBox::StandardButton::Cancel:
            ui->statusBar->showMessage("Ok, programm in work");
        break;
        default:
            ui->statusBar->showMessage("Ok, programm in work");
            break;
        }
    }

    dataDB->CloseConnect();
}
void MainWindow::initTime(){

}
//void MainWindow::initMenuButton(){
//    QPixmap obj;
//    try {
//    obj.loadFromData(dataDB->GetImageOf("Menu", dataDB->SystemTable));
//}  catch(const SyzygyException& ex){
//        auto res = SyzygyException::WhatShow(ex);
//        switch (res) {
//        case QMessageBox::StandardButton::Ok:
//            close();
//            break;
//        case QMessageBox::StandardButton::Cancel:
//            ui->statusBar->showMessage("Ok, programm in work");
//            break;
//        default:
//            ui->statusBar->showMessage("Ok, programm in work");
//            break;
//        }
//    }
//        QIcon ico(obj);
//    //ui->pbMenu->setIcon(ico);
//    //ui->pbMenu->setIconSize(ui->pbMenu->size());
//}

void MainWindow::initPlanet()
{
    earth   = new Planet(ui->earth);
    jupiter = new Planet(ui->jupiter);
    mars    = new Planet(ui->mars);
    mercury = new Planet(ui->mercury);
    neptune = new Planet(ui->neptune);
    saturn  = new Planet(ui->saturn);
    sun     = new Planet(ui->sun);
    uranus  = new Planet(ui->uranus);
    venus   = new Planet(ui->venus);

    planets = {earth, jupiter, mars, mercury, neptune, saturn, sun, uranus, venus};
}

//void MainWindow::on_pbMenu_clicked()
//{
//    algorithms.AllPlanetsMovement(planets, QDate::currentDate());
//    //algorithms.HeliocentricLon(earth, QDate::currentDate());
//    //algorithms.PlanetMovement(saturn, 4.71238898038469); //movement test (270=4.71238898038469)
//    int deltaX = 1, deltaY = 30;
//    if(!isMenuShow)
//        this->setGeometry(this->x()+deltaX, this->y()+deltaY, this->width()+ui->pbMenu->width()*1.5,this->height());
//    isMenuShow = true;
//}
void MainWindow::Tick_of_clock()
{
    clock->Tick();
}


//void MainWindow::on_pbDisMenu_clicked()
//{
//    int deltaX = 1, deltaY = 30;

//    if(isMenuShow)
//        this->setGeometry(this->x()+deltaX, this->y()+deltaY, this->width()- ui->pbMenu->width()*1.5,this->height());

//    isMenuShow = false;
//}


void MainWindow::on_pbTravelToPlanet_clicked()
{
    this->setCursor(travelCursor);
    isTraveling = true;
}


void MainWindow::on_pbSetDate_clicked()
{

}

void MainWindow::on_pbAboutProg_clicked()
{
    aboutProgForm->show();
}

void MainWindow::on_dvlprs_clicked()
{
    dvlprsForm->show();
}

void MainWindow::mousePressEvent(QMouseEvent *me)
{
    if(me->button() == Qt::LeftButton && isTraveling){
        qDebug() <<"Preses" << me->pos().x();
        try
        {
            for(auto planet: planets)
            {
                if(planet->GetX() <= me->pos().x() && planet->GetY() <= me->pos().y() &&
                    me->pos().x() <= planet->GetX()+planet->GetWidth() && me->pos().y() <= planet->GetY()+planet->GetHeight())
                {
                    PlanetInfoData* data = new PlanetInfoData(this->dataDB);
                    emit SendOptionsAndInfo(data->Parse(planet->GetName()));
                    infoForm->show();
                    this->setCursor(Qt::ArrowCursor);
                    isTraveling = false;
                    break;
                }
            }
        }
        catch(const SyzygyException& ex){
            SyzygyException::WhatShow(ex);
        }
    }
}

