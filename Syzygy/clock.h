#ifndef CLOCK_H
#define CLOCK_H
#include <QTimer>
#include <QLCDNumber>
#include <QDateTime>
#include <QObject>
#include <QDebug>
#include <QMainWindow>

class Clock : public QObject
{
public:
    Clock(QLCDNumber *dm,QLCDNumber *y, QLCDNumber *hm, QLCDNumber *s, QMainWindow* mainWindow);
    ~Clock();
    void Start();
    void Stop();
    bool GetisEnable();
private:
    QTimer* timer;
    QLCDNumber *dayAndMonth, *year, *hourAndMin, *second;
    QMainWindow *mw;
    bool isEnable;
    void initSetCurrentTime();

    public slots:
    void Tick();
};

#endif // CLOCK_H
