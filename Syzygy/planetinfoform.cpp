#include "planetinfoform.h"
#include "ui_planetinfoform.h"

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
    if(!data->isEmpty())
    ui->lInfo->setText(data->GetInfo());
    else
        ui->lInfo->setText("ups");
    delete data;
}
