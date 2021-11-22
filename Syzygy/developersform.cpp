#include "developersform.h"
#include "ui_developersform.h"
#include "datafromdb.h"

DevelopersForm::DevelopersForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DevelopersForm)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/Image/solar-system.png"));
    DataFromDB databd;


            // Asya
    auto Asya = databd.GetImageOf("Asya", databd.GitHubTable);
    QPixmap imgAsya;

    imgAsya.loadFromData(Asya);
    ui->asya->setPixmap(imgAsya.scaled(ui->asya->width(), ui->asya->height()));
    ui->asya->setStyleSheet("background: transparent;");

    ui->pbAsyaLink->setText(databd.GetTextOf("Asya", databd.GitHubTable));
    ui->pbAsyaLink->setStyleSheet("background-image: url(:/btnPhoto/Image/BtnsBackGround.jpg);\ncolor: rgb(255, 255, 255)");

            // Max
    auto Max = databd.GetImageOf("Max", databd.GitHubTable);
    QPixmap imgMax;

    imgMax.loadFromData(Max);
    ui->max->setPixmap(imgMax.scaled(ui->max->width(), ui->max->height()));
    ui->max->setStyleSheet("background: transparent;");

    ui->pbMaxLink->setText(databd.GetTextOf("Max", databd.GitHubTable));
    ui->pbMaxLink->setStyleSheet("background-image: url(:/btnPhoto/Image/BtnsBackGround.jpg);\ncolor: rgb(255, 255, 255)");

            // Kate
    auto Kate = databd.GetImageOf("Kate", databd.GitHubTable);
    QPixmap imgKate;

    imgKate.loadFromData(Kate);
    ui->kate->setPixmap(imgKate.scaled(ui->kate->width(), ui->kate->height()));
    ui->kate->setStyleSheet("background: transparent;");

    ui->pbKateLink->setText(databd.GetTextOf("Kate", databd.GitHubTable));
    ui->pbKateLink->setStyleSheet("background-image: url(:/btnPhoto/Image/BtnsBackGround.jpg);\ncolor: rgb(255, 255, 255)");

    databd.CloseConnect();
}

DevelopersForm::~DevelopersForm()
{
    delete ui;
}

void DevelopersForm::on_pbAsyaLink_clicked()
{
    QDesktopServices::openUrl(QUrl(ui->pbAsyaLink->text()));
}

void DevelopersForm::on_pbMaxLink_clicked()
{
    QDesktopServices::openUrl(QUrl(ui->pbMaxLink->text()));
}

void DevelopersForm::on_pbKateLink_clicked()
{
    QDesktopServices::openUrl(QUrl(ui->pbKateLink->text()));
}
