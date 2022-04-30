#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include "QSignalMapper"
#include "dbhelp.h"
#include "updatestudentdialog.h"
#include "updatecoursedialog.h"

namespace Ui {
class admin;
}

class admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();

private:
    Ui::admin *ui;
    dbHelp* dbHelper;
    int currentIndex = 0; //区分 是学生界面 还是 课程界面

private slots:
    void myAction(int);
    void tableClick(int,int);
    void getStudentData();
    void getCourseData();
    void on_add_clicked();

private:
    void initMenu();
    void configTable();
    void initTable();
    void initStudentTable();
    void initCourseTable();
    void clearStudentForm();
    void fillTable(QVector<QVector<QVariant>>&);
    void initTitle();
    QAction* addMenuAction(QString);
};

#endif // ADMIN_H
