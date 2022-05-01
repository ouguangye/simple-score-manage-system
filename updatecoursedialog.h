#ifndef UPDATECOURSEDIALOG_H
#define UPDATECOURSEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "dbhelp.h"
#include "form.h"

namespace Ui {
class updateCourseDialog;
}

class updateCourseDialog : public QDialog,public form
{
    Q_OBJECT

private:
    void initform() override ;
    void initTitle() override;
    void setIdEditAble() override;
    void confirm() override;


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
};

#endif // UPDATECOURSEDIALOG_H
