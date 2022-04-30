#ifndef UPDATESTUDENTDIALOG_H
#define UPDATESTUDENTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "dbhelp.h"

namespace Ui {
class updateStudentDialog;
}

class updateStudentDialog : public QDialog
{
    Q_OBJECT

private:
    void initform();
    void initTitle();
    void setIdEditAble();
public:
    explicit updateStudentDialog(QWidget *,QString);
    explicit updateStudentDialog(QWidget*);
    ~updateStudentDialog();

signals:
    void closeDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::updateStudentDialog *ui;
    dbHelp* dbHelper;
    QString id;
    int type; // 0 表示添加， 1表示更新
};

#endif // UPDATESTUDENTDIALOG_H
