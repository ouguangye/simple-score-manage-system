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

bool dbHelp::excuteHelp(QString s){
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(s)){
        qDebug() << "Error: Fail to excute. " << sqlQuery.lastError()<<endl;
        qDebug()<<s<<endl;
        return false;
    }
    qDebug() << "execute success";
    return true;
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
    QString createSql = "CREATE TABLE IF NOT EXISTS teacher(\
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

bool dbHelp::insertStudent(QString id, QString name,QString sex,int age,QString year,QString student_class){
    QString insertSql = QString("INSERT INTO Student (ID,Name,Sex,Entrance_Age,Entrance_Year,Class)\
                        Values ('%1','%2','%3',%4,'%5','%6');")
            .arg(id).arg(name).arg(sex).arg(age).arg(year).arg(student_class);
    return excuteHelp(insertSql);
}

void dbHelp::getStudentById(QString & id, QString &name, QString & sex, int & age, QString & year, QString &student_class){
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(QString("SELECT * FROM student where ID = '%1'").arg(id)))
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            name = sqlQuery.value(1).toString();
            sex = sqlQuery.value(2).toString();
            age = sqlQuery.value(3).toInt();
            year = sqlQuery.value(4).toString();
            student_class = sqlQuery.value(5).toString();
        }
    }
}

bool dbHelp::updateStudentById(QString & id, QString & name, QString & sex, int & age, QString &year, QString &student_class){
    QString updateSql = QString("update student set Name = '%1', Sex = '%2', Entrance_Age = %3, Entrance_Year = '%4',Class ='%5' where ID = '%6';")
            .arg(name).arg(sex).arg(age).arg(year).arg(student_class).arg(id);
    return excuteHelp(updateSql);
}

bool dbHelp::deleteStudentById(QString id){
    QString deleteSql = QString("delete from Student where ID = '%1'").arg(id);
    return excuteHelp(deleteSql);
}

void dbHelp::insertTeacher(){
    QString s[] = {"insert OR IGNORE into teacher (ID, Name, Course) VALUES ('11111','mao','architecture');",
                   "insert OR IGNORE into teacher (ID, Name, Course) VALUES ('22222','wang','database');",
                   "insert OR IGNORE into teacher (ID, Name, Course) VALUES ('33333','yang','algorithm');"};
    for(QString a:s){
        excuteHelp(a);
    }
}

/*
 * 查询数据表
 * id = 0 查询 Student
*/
QVector<QVector<QVariant>> dbHelp::queryTable(int id){
    QSqlQuery sqlQuery;
    QVector<QVector<QVariant>> list;
    int len = 0;
    QString tableName = "";
    if(id == 0){
        tableName = "Student";
        len = 6;
    }
    if(!sqlQuery.exec("SELECT * FROM " + tableName))
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            QVector<QVariant> tmp;
            for(int i = 0;i<len;i++){
                tmp.push_back(sqlQuery.value(i));
            }
            list.push_back(tmp);
        }
    }
    return list;
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
    return isInTableById("Teacher",id);
}
