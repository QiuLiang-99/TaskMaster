#ifndef DOINGTASK_H
#define DOINGTASK_H

#include <QWidget>
#include "../timecalculater.h"
#include "../taskdata.h"

#include <QObject>
#include <QLabel>
#include <QPainter>
#include "mylabel.h"

namespace Ui {
class doingtask;
}

class doingtask : public QWidget
{
    Q_OBJECT

public:
    explicit doingtask(QWidget *parent = nullptr);
    ~doingtask();

    void settaskname(const QString &taskname);

    void settaskdetail(const QString &taskdetail);
    void settasktime(const QString &tasktime);
    void settimeinday(QTime);


    QTimer *timer;
    QTime   time;
    bool n = false;//isthisstart？
    void startbuttonf(bool&);
    void initForm();
    counttime tasktime;
signals:
    void thistimedone(counttime);
private slots:
    void on_quitButton_clicked();
    void on_startButton_clicked();
    void update();
    void timeEnd();

private:
    Ui::doingtask *ui;
    double sectime;
    QTimer *m_timer;//定时器，用于给计时器发送时间
    MyLabel *timecircle;
};

#endif // DOINGTASK_H
