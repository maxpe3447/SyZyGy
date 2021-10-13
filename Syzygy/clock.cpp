#include "clock.h"

Clock::Clock(QLCDNumber *dm,QLCDNumber *y, QLCDNumber *hm, QLCDNumber *s )
    :dayAndMonth{dm}, year{y}, hourAndMin{hm}, second{s}
{
    timer = new QTimer();
    isEnable = false;
    initSetCurrentTime();

    connect(timer, SIGNAL(timeout()), this, SLOT(Tick()));
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
}
void Clock::Start(){
    isEnable = true;
    timer->start(1);
}
void Clock::Stop(){
    isEnable = false;
    timer->stop();
}
void Clock::Tick(){
    //(!isEnable)     return;
    initSetCurrentTime();

}
