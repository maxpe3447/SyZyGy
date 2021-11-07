#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QDateTime>
#include <QIcon>
#include <QVector>
#include <QDebug>
#include <QMouseEvent>

#include "planet.h"
#include "clock.h"
#include "managesession.h"
#include "planetinfoform.h"
#include "planetinfodata.h"
#include "algorithms.h"
#include "setplanetimage.h"
#include "setplanetimage.h"
#include "aboutprogramform.h"
#include "developersform.h"

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
    void on_pbMenu_clicked();

    void Tick_of_clock();

    void on_pbDisMenu_clicked();

    void on_pbTravelToPlanet_clicked();

    void on_pbSetDate_clicked();

    void on_pb___clicked();

    void on_pbAboutProg_clicked();

    void on_dvlprs_clicked();
private:
signals:
    void SendOptionsAndInfo(PlanetInfoData*);
protected:
    void mouseDoubleClickEvent(QMouseEvent*)override;
private:
    Ui::MainWindow *ui;
    void initPlanetsImage();
    void initTime();
    void initMenuButton();
    void initPlanet();

    bool isMenuShow;
    bool isTraveling;
    QCursor travelCursor;

    SetPlanetImage* imageSetter;
    Clock* clock;
    PlanetInfoForm *infoForm;
    Planet  *earth = nullptr, *jupiter = nullptr, *mars = nullptr, *mercury = nullptr,
            *neptune = nullptr, *saturn = nullptr, *sun = nullptr, *uranus = nullptr, *venus = nullptr;
    QVector<Planet*> planets;
    ManageSession mngSession;
    Algorithms algorithms;
    AboutProgramForm *aboutProgForm;
    DevelopersForm *dvlprsForm;
};
#endif // MAINWINDOW_H
