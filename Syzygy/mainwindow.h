#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QIcon>
#include <QVector>
#include <QMouseEvent>
#include <QDate>
#include <QPainter>
#include <QFile>

#include "planet.h"
#include "clock.h"
#include "managesession.h"
#include "planetinfoform.h"
#include "planetinfodata.h"
#include "algorithms.h"
#include "datafromdb.h"
#include "datafromdb.h"
#include "syzygyexception.h"
#include "aboutprogramform.h"
#include "developersform.h"
#include "setdateform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void Tick_of_clock();

    void on_pbTravelToPlanet_clicked();

    void on_pbSetDate_clicked();

    void on_pbAboutProg_clicked();

    void on_dvlprs_clicked();
private:
signals:
    void SendOptionsAndInfo(PlanetInfoData*);
protected:
    void mousePressEvent(QMouseEvent*)override;
    void paintEvent(QPaintEvent *e) override;
private:
    Ui::MainWindow *ui;

    void initPlanetsImageAndData();
    void initTime();
    void initPlanet();

    void doPainting();

    void SessionRestore();

    bool isTraveling;
    QCursor travelCursor;
    QDate date;

    DataFromDB* dataDB;
    Clock* clock;
    PlanetInfoForm *infoForm;
    Planet  *earth = nullptr, *jupiter = nullptr, *mars = nullptr, *mercury = nullptr,
            *neptune = nullptr, *saturn = nullptr, *sun = nullptr, *uranus = nullptr, *venus = nullptr;
    QVector<Planet*> planets;
    ManageSession mngSession;
    Algorithms* algorithms;
    AboutProgramForm *aboutProgForm;
    DevelopersForm *dvlprsForm;
    SetDateForm *setDateForm;
};
#endif // MAINWINDOW_H
