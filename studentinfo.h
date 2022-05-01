#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QMessageBox>
#include "dbhelp.h"
#include "csearchbox.h"

namespace Ui {
class studentInfo;
}

class studentInfo : public QMainWindow
{
    Q_OBJECT
private:
    void initMenu();
public:
    explicit studentInfo(QWidget *,QString);
    ~studentInfo();

private slots:
    void switchPage(int);
    void getSearchInfo(QString);

private:
    Ui::studentInfo *ui;
    dbHelp* dbHelper;
    QString id;
};

#endif // STUDENTINFO_H
