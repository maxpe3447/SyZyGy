#ifndef ABOUTPROGRAMFORM_H
#define ABOUTPROGRAMFORM_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class AboutProgramForm;
}

class AboutProgramForm : public QWidget
{
    Q_OBJECT

public:
    explicit AboutProgramForm(QWidget *parent = nullptr);
    ~AboutProgramForm();

private:
    Ui::AboutProgramForm *ui;
    void SetLabelStyle(QLabel* l);
};

#endif // ABOUTPROGRAMFORM_H
