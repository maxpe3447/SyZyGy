#include "developersform.h"
#include "ui_developersform.h"

DevelopersForm::DevelopersForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DevelopersForm)
{
    ui->setupUi(this);
    this->setStyleSheet("background-image: url(:/BackGround/Image/BackGroun.jpg);");
}

DevelopersForm::~DevelopersForm()
{
    delete ui;
}
