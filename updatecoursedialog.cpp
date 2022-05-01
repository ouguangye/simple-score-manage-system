#include "updatecoursedialog.h"
#include "ui_updatecoursedialog.h"

updateCourseDialog::updateCourseDialog(QWidget *parent,QString id) :
    QDialog(parent),form(id),
    ui(new Ui::updateCourseDialog)
{
    ui->setupUi(this);
    this->id = id;
    this->type = 1;
    dbHelper = dbHelp::getInstance();
    initform();
    initTitle();
    setIdEditAble();
}

updateCourseDialog::updateCourseDialog(QWidget *parent) :
    QDialog(parent),form(),
    ui(new Ui::updateCourseDialog)
{
    ui->setupUi(this);
    this->type = 0;
    dbHelper = dbHelp::getInstance();
    initTitle();
    setIdEditAble();
}

updateCourseDialog::~updateCourseDialog()
{
    delete ui;
}

void updateCourseDialog::initform(){
    if(type == 0) return;
    QString name="",teacherID = "",grade = "",year="";
    int credit = 0;
    dbHelper->getCourseById(id,name,teacherID,credit,grade,year);
    ui->id->setText(id);
    ui->name->setText(name);
    ui->teacherID->setText(teacherID);
    ui->credit->setText(QString::number(credit));
    ui->grade->setText(grade);
    ui->cancel_year->setText(year);
}

void updateCourseDialog::initTitle(){
    if(type == 1)ui->title->setText("Update Course");
    else ui->title->setText("Add Course");
}

void updateCourseDialog::setIdEditAble(){
    ui->id->setReadOnly(type == 1);
}

void updateCourseDialog::confirm(){
    QString name = ui->name->text();
    QString teacherID = ui->teacherID->text();
    QString grade = ui->grade->text();
    QString year = ui->cancel_year->text();
    int credit = ui->credit->text().toInt();
    if(type == 1){
        if(year != ""){
            if(dbHelper->updateCourseById(id,name,teacherID,credit,grade,year)){
                QMessageBox::information(this, "INFO","update successfully!!!");
            }
        }
        else{
            if(dbHelper->updateCourseById(id,name,teacherID,credit,grade)){
                QMessageBox::information(this, "INFO","update successfully!!!");
            }
        }
    }
    else{
        id = ui->id->text();
        if(year!=""){
            if(dbHelper->insertCourse(id,name,teacherID,credit,grade,year)){
                QMessageBox::information(this, "INFO","add successfully!!!");
            }
        }
        else {
            if(dbHelper->insertCourse(id,name,teacherID,credit,grade)){
                QMessageBox::information(this, "INFO","add successfully!!!");
            }
        }
    }
}

void updateCourseDialog::on_buttonBox_accepted()
{
    confirm();
    emit closeDialog();
    this->close();
}

void updateCourseDialog::on_buttonBox_rejected()
{
    this->close();
}
