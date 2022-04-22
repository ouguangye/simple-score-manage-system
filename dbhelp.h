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
    void excuteHelp(QString);
    void successTip(QString);
public:
    dbHelp();
    void quit();
    void insertStudent(QString, QString,QString,int,QString,QString);
    void queryTable(int id);
    bool isStudentInTableById(QString);
public:
    static dbHelp* getInstance(){
        if(dbHelpInstance == nullptr){
            dbHelpInstance = new dbHelp();
        }
        return dbHelpInstance;
    }

};

#endif // DBHELP_H
