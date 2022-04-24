#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    dbHelper = dbHelp::getInstance();
    initMenu();
    configTable();
    initTable();
}

admin::~admin()
{
    delete ui;
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
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(tableClick(int,int)));
}

void admin::initTable(){
    ui->tableWidget->clear();
    if(currentIndex == 0) initStudentTable();
    else if(currentIndex == 1) initCourseTable();
}

void admin::initStudentTable(){
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setHorizontalHeaderLabels(
                QStringList() << "ID" << "Name" << "Sex"<<"Entrance Age"<<"Entrance Year"<<"Class"<<" "<<" "
                );
    getStudentData();
}

void admin::initCourseTable(){
    ui->tableWidget->setHorizontalHeaderLabels(
                QStringList() << "ID" << "Name" << "Teacher ID"<<"Credit"<<"Grade"<<"Canceled Year"<<" "<<" "
                );
    ui->tableWidget->setColumnCount(8);

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

void admin::myAction(int index){
    currentIndex = index;
    initTable();
}


void admin::tableClick(int row,int col){
    if(col != 6 && col != 7) return;
    if(ui->tableWidget->item(row,col) == nullptr) return;
    QString id = ui->tableWidget->item(row,0)->text();
    if(col == 6){
        updateStudentDialog* w = new updateStudentDialog(this,id);
        connect(w,SIGNAL(closeDialog()),this,SLOT(getStudentData()));
        w->show();
    }
    else{
        QMessageBox::StandardButton result=QMessageBox::question(this, "Tips","确定删除该条数据吗?");
        if(result == QMessageBox::Yes){
            if(dbHelper->deleteStudentById(id)){
                QMessageBox::information(this, "INFO","delete successfully!!!");
                getStudentData();
            }
        }
    }

}

void admin::on_add_clicked()
{
    updateStudentDialog* w = new updateStudentDialog(this);
    connect(w,SIGNAL(closeDialog()),this,SLOT(getStudentData()));
    w->show();
}
