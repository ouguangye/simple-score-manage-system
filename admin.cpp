#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    dbHelper = dbHelp::getInstance();
    initTitle();
    initMenu();
    configTable();
    initTable();
}

admin::~admin()
{
    delete ui;
}

void admin::initTitle(){
    if(currentIndex == 0){
        ui->titleLabel->setText("Student Manage");
    }
    else if(currentIndex == 1 ){
        ui->titleLabel->setText("Course Manage");
    }
}

void admin::initMenu(){
    QSignalMapper *signalMapper = new QSignalMapper(this);
    QAction *manageStudent = addMenuAction("学生管理");
    QAction* manageCourse = addMenuAction("课程管理");
    signalMapper->setMapping(manageStudent,0);
    signalMapper->setMapping(manageCourse,1);
    connect(manageStudent,SIGNAL(triggered()),signalMapper,SLOT(map()));
    connect(manageCourse,SIGNAL(triggered()),signalMapper,SLOT(map()));
    connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(myAction(int)));
}

QAction* admin::addMenuAction(QString s){
    QAction *myAction = new QAction(this);
    myAction->setText(s);
    ui->menu->addAction(myAction);
    return myAction;
}

void admin::configTable(){
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->table,SIGNAL(cellClicked(int,int)),this,SLOT(tableClick(int,int)));
}

void admin::initTable(){
    ui->table->clear();
    if(currentIndex == 0) initStudentTable();
    else if(currentIndex == 1) initCourseTable();
}

void admin::initStudentTable(){
    ui->table->setColumnCount(8);
    ui->table->setHorizontalHeaderLabels(
                QStringList() << "ID" << "Name" << "Sex"<<"Entrance Age"<<"Entrance Year"<<"Class"<<" "<<" "
                );
    getStudentData();
}

void admin::initCourseTable(){
    ui->table->setHorizontalHeaderLabels(
                QStringList() << "ID" << "Name" << "Teacher ID"<<"Credit"<<"Grade"<<"Canceled Year"<<" "<<" "
                );
    ui->table->setColumnCount(8);
    getCourseData();
}

void admin::initChooseTable(){
    ui->table->setHorizontalHeaderLabels(
                QStringList() << "StudentID" << "CourseID" << "TeacherID"<<"ChoosenYear"<<"Score"<<" "<<" "
                );
    ui->table->setColumnCount(7);
    getCourseData();
}

void admin::fillTable(QVector<QVector<QVariant> > & list){
    if(list.empty()) return;
    ui->table->setRowCount(list.length());
    int i = 0;
    for(auto l : list){
        ui->table->setItem(i,0,new QTableWidgetItem(l[0].toString()));
        ui->table->setItem(i,1,new QTableWidgetItem(l[1].toString()));
        ui->table->setItem(i,2,new QTableWidgetItem(l[2].toString()));
        ui->table->setItem(i,3,new QTableWidgetItem(l[3].toString()));
        ui->table->setItem(i,4,new QTableWidgetItem(l[4].toString()));
        ui->table->setItem(i,5,new QTableWidgetItem(l[5].toString()));
        ui->table->setItem(i,6,new QTableWidgetItem(QIcon(QPixmap(":/icon/change.png")),"更改信息"));
        ui->table->setItem(i,7,new QTableWidgetItem(QIcon(QPixmap(":/icon/delete.png")),"删除"));

        ui->table->item(i,6)->setTextColor(QColor(46, 204, 113));
        ui->table->item(i,7)->setTextColor(QColor(255, 71, 87));
        i++;
    }
}

void admin::getStudentData(){
    QVector<QVector<QVariant>> list = dbHelper->queryTable(0);
    fillTable(list);
}

void admin::getCourseData(){
    QVector<QVector<QVariant>> list = dbHelper->queryTable(1);
    fillTable(list);
}

void admin::myAction(int index){
    currentIndex = index;
    initTable();
    initTitle();
}


void admin::tableClick(int row,int col){
    if(col != 6 && col != 7) return;
    if(ui->table->item(row,col) == nullptr) return;
    QString id = ui->table->item(row,0)->text();
    if(col == 6){
        if(currentIndex == 0){
            updateStudentDialog* w = new updateStudentDialog(this,id);
            connect(w,SIGNAL(closeDialog()),this,SLOT(getStudentData()));
            w->show();
        }
        else{
            updateCourseDialog* w = new updateCourseDialog(this,id);
            connect(w,SIGNAL(closeDialog()),this,SLOT(getCourseData()));
            w->show();
        }
    }
    else{
        QMessageBox::StandardButton result=QMessageBox::question(this, "Tips","确定删除该条数据吗?");
        if(result == QMessageBox::Yes){
            if(currentIndex == 0){
                if(dbHelper->deleteStudentById(id)){
                    QMessageBox::information(this, "INFO","delete successfully!!!");
                    getStudentData();
                }
            }
            else{
                if(dbHelper->deleteCourseById(id)){
                    QMessageBox::information(this, "INFO","delete successfully!!!");
                    getCourseData();
                }
            }
        }
    }

}



void admin::on_addBtn_clicked()
{
    if(currentIndex == 0){
        //qDebug()<<"currentIndex: 0"<<endl;
        updateStudentDialog* w = new updateStudentDialog(this);
        connect(w,SIGNAL(closeDialog()),this,SLOT(getStudentData()));
        w->show();
    }
    else if(currentIndex == 1){
        //qDebug()<<"currentIndex: 1"<<endl;
        updateCourseDialog* w = new updateCourseDialog(this);
        connect(w,SIGNAL(closeDialog()),this,SLOT(getCourseData()));
        w->show();
    }
    else{

    }
}
