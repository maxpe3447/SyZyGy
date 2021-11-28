#include "planetinfoform.h"
#include "ui_planetinfoform.h"

#include <QPixmap>

PlanetInfoForm::PlanetInfoForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlanetInfoForm)
{
    ui->setupUi(this);

}

PlanetInfoForm::~PlanetInfoForm()
{
    delete ui;
}

void PlanetInfoForm::GetOptionsAndInfo(PlanetInfoData* data)
{
    if(!data->isEmpty()){
        ui->lInfo->setText(data->GetInfo());
        QPixmap pixmap;
        pixmap.loadFromData(data->GetImg());        

        ui->planeyImg->setPixmap(pixmap.scaled(ui->planeyImg->width(), ui->planeyImg->height()));
        ui->planeyImg->setStyleSheet("background: transparent;");
        ui->lInfo->setStyleSheet("background: transparent;"
                                 "color: rgb(255, 255, 255);"
                                 "border-style: outset;"
                                 "border-width: 3px;"
                                 "border-color: rgb(255, 255, 255)");

        ui->lPlanetName->setText(data->GetUkrName());
        ui->lPlanetName->setStyleSheet("background: transparent;"
                                 "color: rgb(255, 255, 255);"
                                 "border-style: outset;"
                                 "border-width: 3px;"
                                 "border-color: rgb(255, 255, 255)");

        //this->setGeometry(this->x(),this->y(),data->GetWidthForm(),data->GetHeighForm());
        this->setWindowTitle(data->GetUkrName());
        this->setWindowIcon(QIcon(pixmap));
    }
    else
        ui->lInfo->setText("ups");
    delete data;
}
