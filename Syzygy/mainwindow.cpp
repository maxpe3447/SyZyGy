#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), isTraveling(false)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/Image/solar-system.png"));
    ui->groupBox->setStyleSheet("background: transparent; color: rgb(255, 255, 255)");

    date = QDate::currentDate();
    infoForm = new PlanetInfoForm();
    aboutProgForm = new AboutProgramForm();
    dvlprsForm = new DevelopersForm();
    setDateForm = new SetDateForm(&date);

    try {
        dataDB = new DataFromDB();
    }  catch(const SyzygyException& ex){

        if(QMessageBox::StandardButton::Ok == SyzygyException::WhatShow(ex)){
            close();
        }
    }


    initTime();
    initPlanet();
    initPlanetsImageAndData();

    ui->toolBar->setStyleSheet("background: transparent;"
                               "color: rgb(255, 255, 255)");

    clock->Start();

    connect(ui->aboutProg, &QAction::triggered, this, &MainWindow::on_pbAboutProg_clicked);
    connect(ui->dvlprs, &QAction::triggered, this, &MainWindow::on_dvlprs_clicked);

    travelCursor = QCursor(QPixmap("Image/rocket.png"), 0, 0);
    algorithms = new Algorithms(this, planets);

    try {
        SessionRestore();
    }  catch (SyzygyException& ex) {
        SyzygyException::WhatShow(ex);
    }
    connect(this, &MainWindow::SendOptionsAndInfo, infoForm, &PlanetInfoForm::GetOptionsAndInfo);
    connect(setDateForm, &SetDateForm::SendDate, algorithms, &Algorithms::AllPlanetsMovement);
    connect(setDateForm, &SetDateForm::SendDate, clock, &Clock::DateSet);
}

MainWindow::~MainWindow()
{
    mngSession.SetCurrentSession(planets, clock->GetDate());
qDebug() << clock->GetDate().toString("dd.MM.yyyy");

    delete dataDB;
    delete ui;
    delete clock;
    delete algorithms;
    delete infoForm;
    delete aboutProgForm;
    delete dvlprsForm;
    delete setDateForm;


    for(auto planet: planets)
        delete planet;
}

void MainWindow::initPlanetsImageAndData(){
    try{
        for(int i = 0; i < planets.size(); i++){
            if(planets[i] != nullptr){

                auto data = dataDB->GetImageOf(planets[i]->GetName(), "cartoon");
                int radius = dataDB->GetRadiusOf(planets[i]->GetName());
                planets[i]->SetParams(data);
                planets[i]->SetRadius(radius);
                qDebug() <<planets[i]->GetName() << ":" << radius;
            }
        }
    }
    catch(const SyzygyException& ex){

        if(QMessageBox::StandardButton::Ok  == SyzygyException::WhatShow(ex)){
            close();
        }
    }

    dataDB->CloseConnect();
}

void MainWindow::initTime(){
    clock = new Clock(ui->LCDdayAndMonth, ui->LCDYear, ui->LCDHourMin, ui->LCDSecond, this);
}


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

    planets = {sun, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune};
}

void MainWindow::SessionRestore(){
    if(!QFile::exists(mngSession.GetFileName())){
        algorithms->AllPlanetsMovement(&date);
        return;
    }
    auto req = QMessageBox::question(nullptr, "Ви маєте збережену сесію!", "Бажаєте продовжити з попереднього моменту?");
    switch (req) {
     case QMessageBox::StandardButton::Yes:
        mngSession.GetLastSession(planets, date);
        clock->SetDate(date);
        break;
    }
    algorithms->AllPlanetsMovement(&date);
}

void MainWindow::Tick_of_clock()
{
    clock->Tick();
}


void MainWindow::on_pbTravelToPlanet_clicked()
{
    this->setCursor(travelCursor);
    isTraveling = true;
}


void MainWindow::on_pbSetDate_clicked()
{
    setDateForm->show();
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
        qDebug()<<"Cursor: " <<me->pos().x() << " " << me->pos().y();
        try
        {
            for(auto planet: planets)
            {
                if(planet->GetX() <= me->pos().x() && planet->GetY()+ planet->GetHeight() <= me->pos().y() &&
                    me->pos().x() <= planet->GetX()+planet->GetWidth() && me->pos().y() <= planet->GetY()+planet->GetHeight()*2)
                {
                    qDebug()<<"Planet: " <<planet->GetX() << " " << planet->GetY() << "w: " << planet->GetWidth() << "h: " << planet->GetHeight();
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

void MainWindow::paintEvent(QPaintEvent *e) {

  Q_UNUSED(e);

  doPainting();
}

void MainWindow::doPainting() {

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(this->rect(),QPixmap(":/BackGround/Image/BackGroun.jpg").scaled(this->size()));

    painter.setPen(QPen(QBrush("#dbdbdb"), 1));

    /////////////////////////////////////////////////////////////////////////

    painter.drawEllipse(336, 371, mercury->GetRadius()*2,  mercury->GetRadius()*2); // меркурий

    /////////////////////////////////////////////////////////////////////////

    painter.drawEllipse(292, 327, 176, 176); // венера

    /////////////////////////////////////////////////////////////////////////

    painter.drawEllipse(245, 280, 270, 270); // земля

    /////////////////////////////////////////////////////////////////////////

    painter.drawEllipse(202, 237, 356, 356); // марс

    /////////////////////////////////////////////////////////////////////////

    painter.drawEllipse(161, 196, 438, 438); // юпитер

    /////////////////////////////////////////////////////////////////////////

    painter.drawEllipse(112, 147, 536, 536); // сатурн

    /////////////////////////////////////////////////////////////////////////

    painter.drawEllipse(76, 111, 608, 608); // уран

    /////////////////////////////////////////////////////////////////////////

    painter.drawEllipse(24, 59, 712, 712); // плутон

    /////////////////////////////////////////////////////////////////////////

}
