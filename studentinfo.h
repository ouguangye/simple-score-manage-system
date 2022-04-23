#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QMainWindow>
#include <QSignalMapper>
#include "dbhelp.h"

namespace Ui {
class studentInfo;
}

class studentInfo : public QMainWindow
{
    Q_OBJECT
private:
    void initMenu();
    void initform();
public:
    explicit studentInfo(QWidget *,QString);
    ~studentInfo();

private slots:
    void switchPage(int);

    void on_changeBtn_clicked();

private:
    Ui::studentInfo *ui;
    dbHelp* dbHelper;
    QString id;
};

#endif // STUDENTINFO_H
