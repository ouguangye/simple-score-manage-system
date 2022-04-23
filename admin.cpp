#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    initMenu();
}

admin::~admin()
{
    delete ui;
}

void admin::initMenu(){
    QSignalMapper *signalMapper = new QSignalMapper(this);

    QAction *addStudent = new QAction(this);
    QAction *searchTeacher = new QAction(this);

    addStudent->setText("添加学生信息");
    searchTeacher->setText("修改学生信息");

    ui->menu->addAction(addStudent);
    ui->menu->addAction(searchTeacher);

    QAction* info = new QAction(this);
    QAction* myCourse = new QAction(this);

    info->setText("查看个人信息");
    myCourse->setText("查看个人所选课程");

    ui->menu_2->addAction(info);
    ui->menu_2->addAction(myCourse);


    connect(addStudent,SIGNAL(triggered()),signalMapper,SLOT(map()));
    connect(searchTeacher,SIGNAL(triggered()),signalMapper,SLOT(map()));
    connect(info,SIGNAL(triggered()),signalMapper,SLOT(map()));
    connect(myCourse,SIGNAL(triggered()),signalMapper,SLOT(map()));

    signalMapper->setMapping(addStudent,0);
    signalMapper->setMapping(searchTeacher,1);
    signalMapper->setMapping(info,2);
    signalMapper->setMapping(myCourse,3);

    connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(switchPage(int)));
}

void admin::switchPage(int index){
   if(index == 2){
       ui->stackedWidget->setCurrentIndex(index);
       //initform();
   }
}


void admin::on_addStudentBtn_clicked()
{
    QString id = ui->id->text();
    QString name = ui->name->text();
    int age = ui->age->text().toInt();
    QString year = ui->year->text();
    QString student_class = ui->class_2->text();
    QString sex = ui->comboBox->currentIndex() == 0 ? "male":"female";
    dbHelp::getInstance()->insertStudent(id,name,sex,age,year,student_class);
}

void admin::on_clear_clicked()
{
    clearStudentForm();
}

void admin::clearStudentForm(){
    ui->id->clear();
    ui->name->clear();
    ui->age->clear();
    ui->year->clear();
    ui->class_2->clear();
    ui->comboBox->setCurrentIndex(0);
}
