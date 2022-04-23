#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    initMenu();
    initStudentTable();
    dbHelper = dbHelp::getInstance();
}

admin::~admin()
{
    delete ui;
}

void admin::initMenu(){
    QSignalMapper *signalMapper = new QSignalMapper(this);

    QAction *addStudent = new QAction(this);
    QAction *searchTeacher = new QAction(this);

    addStudent->setText("学生信息");

    ui->menu->addAction(addStudent);
    ui->menu->addAction(searchTeacher);

    QAction* info = new QAction(this);
    QAction* myCourse = new QAction(this);

    info->setText("查看个人信息");
    myCourse->setText("查看个人所选课程");

    ui->menu_2->addAction(info);
    ui->menu_2->addAction(myCourse);


    connect(addStudent,SIGNAL(triggered()),signalMapper,SLOT(map()));
    connect(info,SIGNAL(triggered()),signalMapper,SLOT(map()));
    connect(myCourse,SIGNAL(triggered()),signalMapper,SLOT(map()));

    signalMapper->setMapping(addStudent,0);
    signalMapper->setMapping(searchTeacher,1);
    signalMapper->setMapping(info,2);
    signalMapper->setMapping(myCourse,3);

    connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(switchPage(int)));
}

void admin::initStudentTable(){
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(tableClick(int,int)));
    getStudentData();
}

void admin::getStudentData(){
    QVector<QVector<QVariant>> list = dbHelper->queryTable(0);
    if(list.empty()) return;
    ui->tableWidget->setRowCount(list.length());
    int i = 0;
    for(auto l : list){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(l[0].toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(l[1].toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(l[2].toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(l[3].toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(l[4].toString()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(l[5].toString()));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(QIcon(QPixmap(":/icon/change.png")),"更改信息"));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(QIcon(QPixmap(":/icon/delete.png")),"删除"));

        ui->tableWidget->item(i,6)->setTextColor(QColor(46, 204, 113));
        ui->tableWidget->item(i,7)->setTextColor(QColor(255, 71, 87));
        i++;
    }
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
    dbHelper->insertStudent(id,name,sex,age,year,student_class);
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

void admin::tableClick(int row,int col){
    if(col != 6 && col != 7) return;
    QString id = ui->tableWidget->item(0,col)->text();
    if(col == 6){


    }
    else{

    }

}
