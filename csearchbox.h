#ifndef CSEARCHBOX_H
#define CSEARCHBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class CSearchBox : public QWidget
{
    Q_OBJECT
public:
    explicit CSearchBox(QWidget *);
    explicit CSearchBox(QWidget *,int);
    ~CSearchBox();

signals:
    void sigSearch(QString str);
    void sigClear();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void initWidget(int);

public slots:
    void slot_text_Edited(QString str);
    void slot_btn_clicked();

private:
    QLineEdit *m_pLineEdit;
    QPushButton *m_pBtn;
    enum EBtnStatus{ESEARCH, ECLOSE};
    EBtnStatus m_iCurBtnStatus;
};

#endif // CSEARCHBOX_H

