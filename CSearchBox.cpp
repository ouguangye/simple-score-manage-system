#include "csearchbox.h"

#include <QHBoxLayout>
#include <QKeyEvent>
#include "iconhelper.h"

CSearchBox::CSearchBox(QWidget *parent) : QWidget(parent){
   initWidget(20);
}

CSearchBox::CSearchBox(QWidget* parent,int size):QWidget(parent){
    initWidget(size);
}

CSearchBox::~CSearchBox(){
}

void CSearchBox::initWidget(int wsize){
    m_pLineEdit = new QLineEdit(this);
    m_pBtn = new QPushButton(m_pLineEdit);
    QSize size = QSize(wsize, m_pLineEdit->sizeHint().height());
    m_pBtn->setMinimumSize(size);
    m_pBtn->setMaximumSize(size);
    m_pBtn->setFocusPolicy(Qt::NoFocus);
    m_pBtn->setFlat(true);
    m_pBtn->setCursor(QCursor(Qt::PointingHandCursor));
    m_pBtn->setText(tr("Search"));
    m_iCurBtnStatus = ESEARCH;
    IconHelper::Instance()->SetIcon(m_pBtn, 0xf002);
    //0xf002 is search btn icon
    //0xf00d is close btn icon

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_pBtn);
    m_pLineEdit->setLayout(buttonLayout);
    //m_pLineEdit->setGeometry(0,0,size.width(),size.height());
    m_pLineEdit->setTextMargins(0, 1, size.width(), 1);
    m_pLineEdit->installEventFilter(this);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_pLineEdit);
    this->setLayout(mainLayout);


    QString qss = QString("QPushButton {background: gray; color: white; border: 1 solid gray;min-width: 20px;}")
            + QString("QPushButton:hover {background: black; color: white; border: 1 solid black;}")
            + QString("QPushButton:pressed {background: white;color: black;}");
    this->setStyleSheet(qss);

    connect(m_pLineEdit, SIGNAL(textEdited(QString)),
            this, SLOT(slot_text_Edited(QString)) );
    connect(m_pBtn, SIGNAL(clicked()),
            this, SLOT(slot_btn_clicked()));
}

void CSearchBox::slot_text_Edited(QString str)
{
    int iTextLen = str.size();
    if(iTextLen == 0)
    {
        m_iCurBtnStatus = ESEARCH;
        IconHelper::Instance()->SetIcon(m_pBtn, 0xf002);
        emit sigClear();
    }
    else
    {
        m_iCurBtnStatus = ECLOSE;
        IconHelper::Instance()->SetIcon(m_pBtn, 0xf00d);
    }
}

void CSearchBox::slot_btn_clicked()
{
    if(m_iCurBtnStatus == ESEARCH)
    {
        //This is impossible
    }
    else
    {
        m_pLineEdit->clear();
        m_pLineEdit->setFocus();
        m_iCurBtnStatus = ESEARCH;
        IconHelper::Instance()->SetIcon(m_pBtn, 0xf002);
        emit sigClear();
    }
}

bool CSearchBox::eventFilter(QObject *obj, QEvent *event)
{
    if(m_pLineEdit == qobject_cast<QLineEdit*>(obj))
    {
        QString str = m_pLineEdit->text().trimmed();
        if( (str.size() > 0) &&
            (event->type() == QEvent::KeyPress))
        {
            QKeyEvent *keyEvent = (QKeyEvent*)(event);
            if(keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
            {
                m_pLineEdit->setFocus();
                emit sigSearch(str);
                return true;
            }
        }
    }

    return QObject::eventFilter(obj, event);
}


