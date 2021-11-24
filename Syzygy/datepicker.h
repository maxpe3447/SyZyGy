#ifndef DATEPICKER_H
#define DATEPICKER_H

#include <QMainWindow>

namespace Ui {
class DatePicker;
}

class DatePicker : public QMainWindow
{
    Q_OBJECT

public:
    explicit DatePicker(QWidget *parent = nullptr);
    ~DatePicker();

private:
    Ui::DatePicker *ui;
};

#endif // DATEPICKER_H
