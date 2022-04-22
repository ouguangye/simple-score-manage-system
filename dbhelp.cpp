#include "dbhelp.h"

dbHelp *dbHelp::dbHelpInstance = nullptr;

dbHelp::dbHelp()
{
    createDB();
    createStudent();
    createChoose();
    createCourse();
    createTeacher();

    insertTeacher();
}


void dbHelp::quit()
{
    if(database.isOpen()){
        database.close();
        qInfo("Close database success.");
    }
    qInfo("[OK] AppDatabase quit.");
}

void dbHelp::createDB(){
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        // 建立和SQlite数据库的连接
        database = QSqlDatabase::addDatabase("QSQLITE");
        // 设置数据库文件的名字
        database.setDatabaseName("MyDataBase.db");
    }
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        // do something
    }
}

void dbHelp::excuteHelp(QString s){
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(s))
    {
        qDebug() << "Error: Fail to excute. " << sqlQuery.lastError()<<endl;
        qDebug()<<s<<endl;
    }
    else
    {     qDebug() << "execute success";
    }
}

void dbHelp::createStudent(){
    QString createSql = "CREATE TABLE IF NOT EXISTS Student(\
            ID varchar(10) not null primary key,\
            Name varchar(20) not null,\
            Sex varchar(10) not null check(Sex = 'male' or Sex = 'female'),\
            Entrance_Age INT not null check(Entrance_Age between 10 and 50),\
            Entrance_Year varchar(4),\
            Class varchar(10)\
        );";
    excuteHelp(createSql);
}

void dbHelp::createCourse(){
    QString createSql = "CREATE TABLE IF NOT EXISTS Course(\
            ID varchar(7) not null,\
            Name varchar(20) not null,\
            TeacherID varchar(5) not null,\
            Credit INT not null,\
            Grade INT not null,\
            Canceled_Year varchar(20) not null\
        );";
    excuteHelp(createSql);
}

void dbHelp::createTeacher(){
    QString createSql = "CREATE TABLE IF NOT EXISTS teachers(\
            ID varchar(5) not null primary key,\
            Name varchar(20) not null,\
            Course varchar(20) not null\
        ); ";
    excuteHelp(createSql);
}

void dbHelp::createChoose(){
    QString createSql = "CREATE TABLE IF NOT EXISTS choose(\
            studentID varchar(10) not null,\
            courseID varchar(10) not null,\
            teacherID varchar(5) not null\
        );";
    excuteHelp(createSql);
}

void dbHelp::insertStudent(QString id, QString name,QString sex,int age,QString year,QString student_class){
    QString insertSql = QString("INSERT INTO Student (ID,Name,Sex,Entrance_Age,Entrance_Year,Class)\
                        Values ('%1','%2','%3',%4,'%5','%6');")
            .arg(id).arg(name).arg(sex).arg(age).arg(year).arg(student_class);
    excuteHelp(insertSql);
    queryTable(0);
}

void dbHelp::insertTeacher(){
    QString s[] = {"insert OR IGNORE into teachers (ID, Name, Course) VALUES ('11111','mao','architecture');",
                   "insert OR IGNORE into teachers (ID, Name, Course) VALUES ('22222','wang','database');",
                   "insert OR IGNORE into teachers (ID, Name, Course) VALUES ('33333','yang','algorithm');"};
    for(QString a:s){
        excuteHelp(a);
    }
}

void dbHelp::queryTable(int id){
    QSqlQuery sqlQuery;
    if(id == 0){
        if(!sqlQuery.exec("SELECT * FROM student"))
        {
            qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
        }
        else
        {
            while(sqlQuery.next())
            {
                for(int i = 0;i<6;i++) qDebug()<<sqlQuery.value(i)<<" ";
            }
            qDebug()<<endl<<endl;
        }
    }
}

bool dbHelp::isInTableById(QString table,QString id){
    QSqlQuery sqlQuery;
    QString s = QString("select count(*) from %1 where ID= '%2';").arg(table).arg(id);
    if(!sqlQuery.exec(s)){
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else{
        while(sqlQuery.next()){
            if(sqlQuery.isActive()){
                return sqlQuery.value(0).toInt() == 1;
            }
        }
    }
    return false;
}

bool dbHelp::isStudentInTableById(QString id){
   return isInTableById("Student",id);
}

bool dbHelp::isTeacherInTableById(QString id){
    return isInTableById("Teachers",id);
}
