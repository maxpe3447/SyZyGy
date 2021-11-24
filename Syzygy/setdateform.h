#ifndef SETDATEFORM_H
#define SETDATEFORM_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QDateTimeEdit>

namespace Ui {
class SetDateForm;
}

class SetDateForm : public QMainWindow
{
    Q_OBJECT

public:
    SetDateForm(QDateTime *dateTime, QWidget *parent = nullptr);
    ~SetDateForm();

private slots:
    void on_passDate_clicked();

private:
    Ui::SetDateForm *ui;
    QDateTime *dateTime;
};


#endif // SETDATEFORM_H
