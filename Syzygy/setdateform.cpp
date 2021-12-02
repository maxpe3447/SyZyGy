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

    ui->setDate->setMinimumDate(QDate(973, 6, 5));
    ui->setDate->setMaximumDate(QDate(3026, 7, 25));

    ui->DateList->setStyleSheet("QComboBox::view() {color: rgb(83, 122, 176);}");

    FillingDateBox();
}

SetDateForm::~SetDateForm()
{
    delete ui;
}

void SetDateForm::on_passDate_clicked()
{
    if(ui->DateList->currentText() != "Цікаві дати...")
    {
        *date = (QDate::fromString(ui->DateList->currentText(), "dd.MM.yyyy"));
        ui->setDate->setDate(*date);
        emit SendDate(date);
        return;
    }
    if(ui->setDate->date() != QDate::currentDate() && ui->DateList->currentText() == "Цікаві дати...")
    {
        *date = ui->setDate->date();
        emit SendDate(date);
    }

}

void SetDateForm::FillingDateBox()
{
    ui->DateList->addItem("Цікаві дати...");
    ui->DateList->addItem("10.10.1010");
    ui->DateList->addItem("07.09.1581");
    ui->DateList->addItem("02.02.1962");
    ui->DateList->addItem("28.02.1962");
    ui->DateList->addItem("10.03.1982");
    ui->DateList->addItem("18.04.2002");
    ui->DateList->addItem("02.05.2011");
    ui->DateList->addItem("04.07.2020");
    ui->DateList->addItem("12.02.2021");
    ui->DateList->addItem("06.08.2040");
    ui->DateList->addItem("08.02.2169");
    ui->DateList->addItem("05.07.2387");
    ui->DateList->addItem("15.12.2854");
    ui->DateList->addItem("22.04.2945");
    ui->DateList->addItem("28.07.2982");
}
