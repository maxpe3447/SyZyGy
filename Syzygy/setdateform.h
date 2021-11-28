#ifndef SETDATEFORM_H
#define SETDATEFORM_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QDate>

namespace Ui {
class SetDateForm;
}

class SetDateForm : public QMainWindow
{
    Q_OBJECT

public:
    SetDateForm(QDate *dateTime, QWidget *parent = nullptr);
    ~SetDateForm();

signals:
    void SendDate(QDate*);

private slots:
    void on_passDate_clicked();

private:
    Ui::SetDateForm *ui;
    QDate *date;
};


#endif // SETDATEFORM_H
