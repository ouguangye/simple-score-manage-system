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
    QString id = ui->id->text();
    int identify = ui->comboBox->currentIndex();
    if(identify == 0){
        if(dbHelp::getInstance()->isStudentInTableById(id)){
            qDebug()<<"Login successfully";
        }
        else qDebug()<<"Login false";
    }
}

void Login::on_registeredBtn_clicked()
{
    Register* r = new Register;
    r->show();
    this->close();
}
