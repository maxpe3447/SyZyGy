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
    ui->planeyImg->setPixmap(pixmap);
    ui->planeyImg->setPixmap(pixmap.scaled(ui->planeyImg->width(), ui->planeyImg->height()));
    ui->planeyImg->setStyleSheet("background: transparent;");
    }
    else
        ui->lInfo->setText("ups");
    delete data;
}
