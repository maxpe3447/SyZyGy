#include "setdateform.h"
#include "ui_setdateform.h"

SetDateForm::SetDateForm(QDate *date, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SetDateForm)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/Image/solar-system.png"));
    this->setWindowTitle("Вибір дати");

    ui->lInfo->setStyleSheet("background: transparent;"
                             "color: rgb(255, 255, 255);");
    ui->setDate->setDate(QDate::currentDate());
    this->date = date;
}

SetDateForm::~SetDateForm()
{
    delete ui;
}

void SetDateForm::on_passDate_clicked()
{
    *date = ui->setDate->date();
    emit SendDate(date);
}
