#ifndef ABOUTPROGRAMFORM_H
#define ABOUTPROGRAMFORM_H

#include <QMainWindow>
#include <QLabel>
#include <QDebug>

namespace Ui {
class AboutProgramForm;
}

class AboutProgramForm : public QMainWindow
{
    Q_OBJECT

public:
    AboutProgramForm(QWidget *parent = nullptr);
    ~AboutProgramForm();

private:
    Ui::AboutProgramForm *ui;
};

#endif // ABOUTPROGRAMFORM_H
