#include "clock.h"

Clock::Clock(QLCDNumber *dm,QLCDNumber *y, QLCDNumber *hm, QLCDNumber *s )
    :dayAndMonth{dm}, year{y}, hourAndMin{hm}, second{s}
{
    iniSetCurrentTime();

}
Clock::~Clock(){}
void Clock::iniSetCurrentTime(){
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

}
