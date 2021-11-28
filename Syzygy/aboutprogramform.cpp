#include "aboutprogramform.h"
#include "ui_aboutprogramform.h"

AboutProgramForm::AboutProgramForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AboutProgramForm)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/Image/solar-system.png"));
}

AboutProgramForm::~AboutProgramForm()
{
    delete ui;
}



