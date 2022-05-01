#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    dbHelper = dbHelp::getInstance();
    ui->stackedWidget->setCurrentIndex(0);
    CSearchBox *pSearchBtn = new CSearchBox(ui->stackedWidget->widget(0));
    ui->head->addWidget(pSearchBtn);
    connect(pSearchBtn, SIGNAL(sigSearch(QString)),this, SLOT(getSearchInfo(QString)));
}

Login::~Login()
{
    delete ui;
}


void Login::on_loginBtn_clicked()
{
    QString id = ui->id->text();
    //int identify = ui->comboBox->currentIndex();
    QString identify = ui->comboBox->currentText();
    if(identify == "Student"){
        /*
        if(dbHelper->isStudentInTableById(id)){
            studentInfo* s = new studentInfo(nullptr,id);
            s->show();
            this->close();
        }
        else qDebug()<<"Login false";
        */
    }
    else if(identify == "Teacher"){
        if(dbHelper->isTeacherInTableById(id)){
            qDebug()<<"Login successfully";
        }
        else qDebug()<<"Login false";
    }
    else{
        if(id == "12345"){
           admin* adminWindow = new admin;
           adminWindow->show();
           this->close();
        }
        else qDebug()<<"Login false";
    }
}

void Login::getSearchInfo(QString word){
    QMessageBox::information(this, "test", word);
}

void Login::on_commandLinkButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
