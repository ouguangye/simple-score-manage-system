#ifndef UPDATECOURSEDIALOG_H
#define UPDATECOURSEDIALOG_H

#include <QDialog>

namespace Ui {
class updateCourseDialog;
}

class updateCourseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit updateCourseDialog(QWidget *parent = nullptr);
    ~updateCourseDialog();

private:
    Ui::updateCourseDialog *ui;
};

#endif // UPDATECOURSEDIALOG_H
