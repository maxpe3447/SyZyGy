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
//Q_OBJECT
public:
    Clock(QLCDNumber *dm,QLCDNumber *y, QLCDNumber *hm, QLCDNumber *s, QMainWindow* mainWindow);
    ~Clock();
    void Start();
    void Stop();
private:
    QTimer* timer;
    QLCDNumber *dayAndMonth, *year, *hourAndMin, *second;
    QMainWindow *mw;
    bool isEnable;

    void initSetCurrentTime();

    private slots:
    void Tick();
};

#endif // CLOCK_H
