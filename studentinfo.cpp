#include "studentinfo.h"
#include "ui_studentinfo.h"

studentInfo::studentInfo(QWidget *parent,QString id) :
    QMainWindow(parent),
    ui(new Ui::studentInfo)
{
    ui->setupUi(this); 
    this->id = id;
    initMenu();
    ui->stackedWidget->setCurrentIndex(0);
    dbHelper = dbHelp::getInstance();
}

studentInfo::~studentInfo()
{
    delete ui;
}

void studentInfo::initMenu(){
    QSignalMapper *signalMapper = new QSignalMapper(this);

    QAction *searchCourse = new QAction(this);
    QAction *searchTeacher = new QAction(this);

    searchCourse->setText("搜索学校课程");
    searchTeacher->setText("搜索学校老师");

    ui->menu->addAction(searchCourse);
    ui->menu->addAction(searchTeacher);

    QAction* info = new QAction(this);
    QAction* myCourse = new QAction(this);

    info->setText("查看个人信息");
    myCourse->setText("查看个人所选课程");

    ui->menu_2->addAction(info);
    ui->menu_2->addAction(myCourse);
    
    
    connect(searchCourse,SIGNAL(triggered()),signalMapper,SLOT(map()));
    connect(searchTeacher,SIGNAL(triggered()),signalMapper,SLOT(map()));
    connect(info,SIGNAL(triggered()),signalMapper,SLOT(map()));
    connect(myCourse,SIGNAL(triggered()),signalMapper,SLOT(map()));

    signalMapper->setMapping(searchCourse,0);
    signalMapper->setMapping(searchTeacher,1);
    signalMapper->setMapping(info,2);
    signalMapper->setMapping(myCourse,3);

    connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(switchPage(int)));
}

void studentInfo::switchPage(int index){
   if(index == 2){
       ui->stackedWidget->setCurrentIndex(index);
       initform();
   }
}

void studentInfo::initform(){
    QString name = "", sex = "", year = "", student_class="";
    int age = 0;
    dbHelper->getStudentById(id,name,sex,age,year,student_class);
    ui->id_label->setText(id);
    ui->year->setText(year);
    ui->class_2->setText(student_class);
    ui->comboBox->setCurrentIndex(sex == "female");
    ui->name->setText(name);
    ui->age->setText(QString::number(age));
}

void studentInfo::on_changeBtn_clicked()
{
    QString name = ui->name->text();
    QString sex = ui->comboBox->currentIndex() == 0 ? "male" : "female";
    QString year = ui->year->text();
    QString student_class = ui->class_2->text();
    int age = ui->age->text().toInt();
    dbHelper->updateStudentById(id,name,sex,age,year,student_class);
}
