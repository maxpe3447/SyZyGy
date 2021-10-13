#ifndef CLOCK_H
#define CLOCK_H
#include <QTimer>
#include <QLCDNumber>
#include <QDateTime>

class Clock
{
public:
    Clock(QLCDNumber *dm,QLCDNumber *y, QLCDNumber *hm, QLCDNumber *s);
    ~Clock();
    void Start();
private:
    QTimer* clock;
    QLCDNumber *dayAndMonth, *year, *hourAndMin, *second;

    void iniSetCurrentTime();

    private slots:
    void Tick();
};

#endif // CLOCK_H
