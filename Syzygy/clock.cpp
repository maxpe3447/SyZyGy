#include "clock.h"

Clock::Clock(QLCDNumber *dm,QLCDNumber *y, QLCDNumber *hm, QLCDNumber *s, QMainWindow* mainWindow )
    :dayAndMonth{dm}, year{y}, hourAndMin{hm}, second{s}, mw{mainWindow}
{
    date = QDate::currentDate();
    timer = new QTimer(this);
    isEnable = true;
    isShowCurDate = true;
    initSetCurrentTime();

    connect(timer, SIGNAL(timeout()),mw, SLOT(Tick_of_clock()));
    timer->start(1000);
}

Clock::~Clock(){
    delete timer;
}

void Clock::initSetCurrentTime(){
    if(isShowCurDate){
    dayAndMonth->display(QDateTime::currentDateTime().toString("dd.MM"));
    dayAndMonth->setStyleSheet("background: transparent;");

    year->display(QDateTime::currentDateTime().toString(".yyyy"));
    year->setStyleSheet("background: transparent;");
}
    hourAndMin->setStyleSheet("background: transparent;");
    hourAndMin->display(QDateTime::currentDateTime().toString("hh:mm"));

    second->setStyleSheet("background: transparent;");
    second->display(QDateTime::currentDateTime().toString(":ss"));
}

void Clock::Start(){
    isEnable = true;
    timer->start(1000);
}

void Clock::Stop(){
    isEnable = false;
    timer->stop();
}

bool Clock::GetisEnable() const
{
    return isEnable;
}

bool Clock::GetIsShowCurDate() const
{
    return isShowCurDate;
}

QDate Clock::GetDate() const
{
    return date;
}

void Clock::SetIsShowCurDate(bool flag)
{
    isShowCurDate = flag;
}

void Clock::SetDate(QDate date)
{
    SetIsShowCurDate(false);
    this->date = date;

    dayAndMonth->display(date.toString("dd.MM"));
    dayAndMonth->setStyleSheet("background: transparent;");

    year->display(date.toString(".yyyy"));
    year->setStyleSheet("background: transparent;");
}
void Clock::Tick(){
    if(!isEnable)
        return;
    initSetCurrentTime();

}

void Clock::DateSet(QDate* date)
{
    SetDate(*date);
}

