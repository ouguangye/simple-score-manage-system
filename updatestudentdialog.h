#ifndef UPDATESTUDENTDIALOG_H
#define UPDATESTUDENTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "dbhelp.h"
#include "form.h"

namespace Ui {
class updateStudentDialog;
}

class updateStudentDialog : public QDialog,public form
{
    Q_OBJECT

private:
    void initform() override ;
    void initTitle() override;
    void setIdEditAble() override;
    void confirm() override;

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
};

#endif // UPDATESTUDENTDIALOG_H
