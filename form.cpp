#include "form.h"

form::form(){
    this->type = 0;
    dbHelper = dbHelp::getInstance();
    //initTitle();
    //setIdEditAble();
}

form::form(QString id){
    this->id = id;
    this->type = 1;
    dbHelper = dbHelp::getInstance();
    //initform();
    //initTitle();
    //setIdEditAble();
}

void form::initform(){

}

void form::confirm(){

}

void form::initTitle(){

}

void form::setIdEditAble(){

}
