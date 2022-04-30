#ifndef DBHELP_H
#define DBHELP_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class dbHelp
{
private:
    QSqlDatabase database;
    static dbHelp* dbHelpInstance;
private:
    void createDB();
    void createStudent();
    void createCourse();
    void createTeacher();
    void createChoose();
    bool excuteHelp(QString);
    void successTip(QString);
    void insertTeacher();
    bool isInTableById(QString,QString);
public:
    dbHelp();
    void quit();
    bool insertStudent(QString, QString,QString,int,QString,QString);
    void getStudentById(QString&, QString&,QString&,int&,QString&,QString&);
    bool updateStudentById(QString&, QString&,QString&,int&,QString&,QString&);
    bool deleteStudentById(QString);
    QVector<QVector<QVariant>> queryTable(int);
    bool isStudentInTableById(QString);
    bool isTeacherInTableById(QString);
    bool insertCourse(QString,QString,QString,int,QString,QString);
    bool insertCourse(QString,QString,QString,int,QString);
    void getCourseById(QString&,QString&,QString&,int&,QString&,QString&);
    bool updateCourseById(QString&,QString&,QString&,int&,QString&,QString&);
    bool updateCourseById(QString&,QString&,QString&,int&,QString&);
    bool deleteCourseById(QString);
public:
    static dbHelp* getInstance(){
        if(dbHelpInstance == nullptr){
            dbHelpInstance = new dbHelp();
        }
        return dbHelpInstance;
    }

};

#endif // DBHELP_H
