#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_rigisterBtn_clicked()
{
    QString id = ui->id->text();
    QString name = ui->name->text();
    int age = ui->age->text().toInt();
    QString year = ui->year->text();
    QString student_class = ui->class_2->text();
    QString sex = ui->comboBox->currentIndex() == 0 ? "male":"female";
    dbHelp::getInstance()->insertStudent(id,name,sex,age,year,student_class);
}

void Register::on_pushButton_clicked()
{
    Login* l = new Login;
    l->show();
    this->close();
}
