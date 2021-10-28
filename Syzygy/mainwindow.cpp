#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), isMenuShow{false}
{
    ui->setupUi(this);
    ui->groupBox->setStyleSheet("background: transparent;");

    clock = new Clock(ui->LCDdayAndMonth, ui->LCDYear, ui->LCDHourMin, ui->LCDSecond, this);
    imageSeter = new SetPlanetImage();
    infoForm = new PlanetInfoForm();

    initTime();
    initPlanet();
    initPlanetsImage();
    initMenuButton();

    mngSession.GetLastSession(planets);

    clock->Start();

    connect(this, &MainWindow::SendOptionsAndInfo, infoForm, &PlanetInfoForm::GetOptionsAndInfo);
}

MainWindow::~MainWindow()
{
    mngSession.SetCurrentSession(planets);

    for(auto planet: planets)
        delete planet;

    delete imageSeter;
    delete ui;
    delete clock;
    delete infoForm;
}
void MainWindow::initPlanetsImage(){

    for(int i = 0; i < planets.size(); i++){
        if(planets[i] != nullptr){

            auto data = spi.GetImageOf(planets[i]->GetName());
            planets[i]->SetParams(data);
        }
    }

}
void MainWindow::initTime(){

}
void MainWindow::initMenuButton(){
    QPixmap obj("Image/menu.png");
    QIcon ico(obj);
    ui->pbMenu->setIcon(ico);
    ui->pbMenu->setIconSize(ui->pbMenu->size());
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

    planets = {earth, jupiter, mars, mercury, neptune, saturn, sun, uranus, venus};
}

void MainWindow::on_pbMenu_clicked()
{
    //earth.SetPos(100, 100);
    algorithms.PlanetMovement(saturn, 4.71238898038469); //movement test (270=4.71238898038469)
    int deltaX = 1, deltaY = 30;
    if(!isMenuShow)
        this->setGeometry(this->x()+deltaX, this->y()+deltaY, this->width()+ui->pbMenu->width()*1.5,this->height());
    isMenuShow = true;
}
void MainWindow::Tick_of_clock()
{
    clock->Tick();
}


void MainWindow::on_pbDisMenu_clicked()
{
    int deltaX = 1, deltaY = 30;

    if(isMenuShow)
        this->setGeometry(this->x()+deltaX, this->y()+deltaY, this->width()- ui->pbMenu->width()*1.5,this->height());

    isMenuShow = false;
}


void MainWindow::on_pbTravelToPlanet_clicked()
{

}


void MainWindow::on_pbSetDate_clicked()
{

}


void MainWindow::on_pb___clicked()
{

}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *me)
{
    if(me->button() == Qt::LeftButton){
        qDebug() <<"Preses" << me->pos().x();
        for(auto planet: planets){
            //qDebug() <<"("<< me->pos().x() << me->pos().y()<<")\t(" << planet->GetX() << planet->GetY()<<")\t(" << planet->GetX()+planet->GetWidth() << planet->GetY()<<")";
            if(planet->GetX() <= me->pos().x() && planet->GetY() <= me->pos().y() &&
                    me->pos().x() <= planet->GetX()+planet->GetWidth() && me->pos().y() <= planet->GetY()+planet->GetHeight())
            {
//qDebug() <<"!!!!!!!!";
                PlanetInfoData* data = new PlanetInfoData();
                emit SendOptionsAndInfo(data->Parse(planet->GetName()));
                infoForm->show();
                break;
            }
        }
    }
}

