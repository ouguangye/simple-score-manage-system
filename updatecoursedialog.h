#ifndef UPDATECOURSEDIALOG_H
#define UPDATECOURSEDIALOG_H

#include <QDialog>
#include "dbhelp.h"
#include <QMessageBox>

namespace Ui {
class updateCourseDialog;
}

class updateCourseDialog : public QDialog
{
    Q_OBJECT

private:
    void initform();
    void initTitle();
    void setIdEditAble();

public:
    explicit updateCourseDialog(QWidget *,QString);
    explicit updateCourseDialog(QWidget *);
    ~updateCourseDialog();

signals:
    void closeDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::updateCourseDialog *ui;
    dbHelp* dbHelper;
    QString id;
    int type; // 0 表示添加， 1表示更新
};

#endif // UPDATECOURSEDIALOG_H
