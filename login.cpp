#include "login.h"
#include "ui_login.h"
#include "register.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    dbHelper = dbHelp::getInstance();
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
        if(dbHelper->isStudentInTableById(id)){
            studentInfo* s = new studentInfo(nullptr,id);
            s->show();
            this->close();
        }
        else qDebug()<<"Login false";
    }
    else if(identify == 1){
        if(dbHelper->isTeacherInTableById(id)){
            qDebug()<<"Login successfully";
        }
        else qDebug()<<"Login false";
    }
    else{
        if(id == "12345"){
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

void Login::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0) {
        ui->registeredBtn->setHidden(false);
    }
    else{
        ui->registeredBtn->setHidden(true);
    }
}
