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

void PlanetInfoForm::GetOptionsAndInfo(QString msg)
{
    ui->lInfo->setText(msg);
}
