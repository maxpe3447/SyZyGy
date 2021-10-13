#ifndef CLOCK_H
#define CLOCK_H
#include <QTimer>
#include <QLCDNumber>
#include <QDateTime>
#include <QObject>
class Clock : public QObject
{

public:
    Clock(QLCDNumber *dm,QLCDNumber *y, QLCDNumber *hm, QLCDNumber *s);
    ~Clock();
    void Start();
    void Stop();
private:
    QTimer* timer;
    QLCDNumber *dayAndMonth, *year, *hourAndMin, *second;

    bool isEnable;

    void initSetCurrentTime();

    private slots:
    void Tick();
};

#endif // CLOCK_H
