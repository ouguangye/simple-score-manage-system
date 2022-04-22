#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>
#include "dbhelp.h"
#include "login.h"

namespace Ui {
class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_rigisterBtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::Register *ui;

};

#endif // REGISTER_H
