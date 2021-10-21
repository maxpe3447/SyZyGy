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

    bool isMenuShow;

    ManageSession mngSession;
    Clock* clock;
    PlanetInfoForm *infoForm;
    Planet earth, jupiter, mars, mercury, neptune, saturn, sun, uranus, venus;
    QVector<Planet*> planets = {&earth, &jupiter, &mars, &mercury, &neptune, &saturn, &sun, &uranus, &venus};
};
#endif // MAINWINDOW_H
