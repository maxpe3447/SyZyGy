#include "datepicker.h"
#include "ui_datepicker.h"

DatePicker::DatePicker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DatePicker)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/Image/solar-system.png"));
}

DatePicker::~DatePicker()
{
    delete ui;
}
