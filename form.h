#ifndef FORM_H
#define FORM_H
#include "dbhelp.h"

class form
{
public:
    form();
    form(QString);
protected:
    virtual void initform();
    virtual void initTitle();
    virtual void setIdEditAble();
    virtual void confirm();
protected:
    dbHelp* dbHelper;
    QString id;
    int type; // 0 表示添加， 1表示更新
};

#endif // FORM_H
