#include "updatecoursedialog.h"
#include "ui_updatecoursedialog.h"

updateCourseDialog::updateCourseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateCourseDialog)
{
    ui->setupUi(this);
}

updateCourseDialog::~updateCourseDialog()
{
    delete ui;
}
