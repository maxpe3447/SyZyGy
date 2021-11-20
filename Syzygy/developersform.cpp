#include "developersform.h"
#include "ui_developersform.h"
#include "datafromdb.h"

DevelopersForm::DevelopersForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DevelopersForm)
{
    ui->setupUi(this);
    DataFromDB databd;

    auto img = databd.GetImageOf("Asya", databd.GitHubTable);
    QPixmap imgAsya;
    //qDebug()<< img;

    imgAsya.loadFromData(img);
    ui->asya->setPixmap(imgAsya.scaled(ui->asya->width(), ui->asya->height()));
    ui->asya->setStyleSheet("background: transparent;");

    //ui->max->setText(databd.GetTextOf("Asya", databd.GitHubTable));
    databd.CloseConnect();
}

DevelopersForm::~DevelopersForm()
{
    delete ui;
}
