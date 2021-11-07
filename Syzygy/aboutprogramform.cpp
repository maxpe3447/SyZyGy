#include "aboutprogramform.h"
#include "ui_aboutprogramform.h"

AboutProgramForm::AboutProgramForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutProgramForm)
{
    ui->setupUi(this);

    SetLabelStyle(ui->lname);
    SetLabelStyle(ui->ltext);
    SetLabelStyle(ui->ltexttravel);
    SetLabelStyle(ui->ltextdata);
    SetLabelStyle(ui->ltextfunc);
}

AboutProgramForm::~AboutProgramForm()
{
    delete ui;
}

void AboutProgramForm::SetLabelStyle(QLabel *l)
{
    l->setStyleSheet("background: transparent;"
                     "color: rgb(255, 255, 255);"
                     "border-style: outset;"
                     "border-width: 3px;"
                     "border-color: rgb(255, 255, 255)");
}



