#include "developersform.h"
#include "ui_developersform.h"

DevelopersForm::DevelopersForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DevelopersForm)
{
    ui->setupUi(this);
}

DevelopersForm::~DevelopersForm()
{
    delete ui;
}
