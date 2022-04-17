#include "login.h"
#include "ui_login.h"
#include "register.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}


void Login::on_loginBtn_clicked()
{

}

void Login::on_registeredBtn_clicked()
{
    Register* r = new Register;
    r->show();
    this->close();
}
