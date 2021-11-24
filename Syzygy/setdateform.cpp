#include "setdateform.h"
#include "ui_setdateform.h"

SetDateForm::SetDateForm(QDateTime *dateTime, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SetDateForm)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/Image/solar-system.png"));
    this->setWindowTitle("Вибір дати");

    ui->lInfo->setStyleSheet("background: transparent;"
                             "color: rgb(255, 255, 255);");
    this->dateTime = dateTime;
}

SetDateForm::~SetDateForm()
{
    delete ui;
}

void SetDateForm::on_passDate_clicked()
{
    *dateTime = ui->setDate->dateTime();
}
