#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "dbhelp.h"
#include "studentinfo.h"
#include "admin.h"
#include "csearchbox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_loginBtn_clicked();
    void switchPage(int);
    void getSearchInfo(QString);

private:
    Ui::Login *ui;
    dbHelp* dbHelper;

};
#endif // LOGIN_H
