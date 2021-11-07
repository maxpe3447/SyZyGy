#include "aboutprogramform.h"
#include "ui_aboutprogramform.h"

AboutProgramForm::AboutProgramForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AboutProgramForm)
{
    ui->setupUi(this);
}

AboutProgramForm::~AboutProgramForm()
{
    delete ui;
}



