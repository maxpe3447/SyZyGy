#include "clock.h"

Clock::Clock(QLCDNumber *dm,QLCDNumber *y, QLCDNumber *hm, QLCDNumber *s, QMainWindow* mainWindow )
    :dayAndMonth{dm}, year{y}, hourAndMin{hm}, second{s}, mw{mainWindow}
{
    timer = new QTimer(this);
    isEnable = false;
    initSetCurrentTime();

    connect(timer, SIGNAL(timeout()),mw, SLOT(Tick_of_clock()));
    timer->start(1000);
}
Clock::~Clock(){delete timer;}
void Clock::initSetCurrentTime(){
    dayAndMonth->display(QDateTime::currentDateTime().toString("dd.MM"));
    dayAndMonth->setStyleSheet("background: transparent;");

    year->display(QDateTime::currentDateTime().toString(".yyyy"));
    year->setStyleSheet("background: transparent;");

    hourAndMin->setStyleSheet("background: transparent;");
    hourAndMin->display(QDateTime::currentDateTime().toString("hh:mm"));

    second->setStyleSheet("background: transparent;");
    second->display(QDateTime::currentDateTime().toString(":ss"));
    //qDebug() << QDateTime::currentDateTime().toString(":ss");
}
void Clock::Start(){
    isEnable = true;
    timer->start(1000);
}
void Clock::Stop(){
    isEnable = false;
    timer->stop();
}

bool Clock::GetisEnable()
{
    return isEnable;
}
void Clock::Tick(){
    //(!isEnable)     return;
    initSetCurrentTime();

}

