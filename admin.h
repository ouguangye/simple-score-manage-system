#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include "QSignalMapper"
#include "dbhelp.h"
#include "updatestudentdialog.h"

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

private slots:
    void switchPage(int);
    void on_addStudentBtn_clicked();
    void on_clear_clicked();
    void tableClick(int,int);
    void getStudentData();

    void on_pushButton_clicked();

private:
    void initMenu();
    void initStudentTable();
    void clearStudentForm();

};

#endif // ADMIN_H
