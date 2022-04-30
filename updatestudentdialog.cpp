#include "updatestudentdialog.h"
#include "ui_updatestudentdialog.h"

updateStudentDialog::updateStudentDialog(QWidget *parent,QString id) :
    QDialog(parent),
    ui(new Ui::updateStudentDialog)
{
    ui->setupUi(this);
    this->id = id;
    this->type = 1;
    dbHelper = dbHelp::getInstance();
    initform();
    initTitle();
    setIdEditAble();
}

updateStudentDialog::updateStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateStudentDialog)
{
    ui->setupUi(this);
    this->type = 0;
    dbHelper = dbHelp::getInstance();
    initTitle();
    setIdEditAble();
}

updateStudentDialog::~updateStudentDialog()
{
    delete ui;
}

void updateStudentDialog::initform(){
    if(type == 0) return;
    QString name = "", sex = "", year = "", student_class="";
    int age = 0;
    dbHelper->getStudentById(id,name,sex,age,year,student_class);
    ui->id->setText(id);
    ui->year->setText(year);
    ui->class_2->setText(student_class);
    ui->comboBox->setCurrentIndex(sex == "female");
    ui->name->setText(name);
    ui->age->setText(QString::number(age));
}

void updateStudentDialog::initTitle(){
    if(type == 1)ui->title->setText("Update Student");
    else ui->title->setText("Add Student");
}

void updateStudentDialog::setIdEditAble(){
    ui->id->setReadOnly(type == 1);
}

void updateStudentDialog::on_buttonBox_accepted()
{
    QString name = ui->name->text();
    QString sex = ui->comboBox->currentIndex() == 0 ? "male" : "female";
    QString year = ui->year->text();
    QString student_class = ui->class_2->text();
    int age = ui->age->text().toInt();
    if(type == 1){
        if(dbHelper->updateStudentById(id,name,sex,age,year,student_class)){
          QMessageBox::information(this, "INFO","update successfully!!!");
        }
    }
    else{
        QString newID = ui->id->text();
        if(dbHelper->insertStudent(newID,name,sex,age,year,student_class)){
          QMessageBox::information(this, "INFO","Add successfully!!!");
        }
    }
    emit closeDialog();
}
