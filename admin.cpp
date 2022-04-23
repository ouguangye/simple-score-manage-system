#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
}

admin::~admin()
{
    delete ui;
}

void admin::initMenu(){
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

void admin::switchPage(int index){
   if(index == 2){
       ui->stackedWidget->setCurrentIndex(index);
       //initform();
   }
}
