#ifndef TASKDATA_H
#define TASKDATA_H

#include <QString>
#include <QDate>
#include <QDataStream>
#include <QFile>
#include <QDebug>
struct counttime{
    QTime start;
    QTime end;
    QTime total;
    counttime() {start = {0,0,0},end = {0,0,0}, total = {0,0,0};}
};
struct taskdata
{
    QString taskname;
    QString taskdetail;

    int taskid;
    int taskstate;

    QDate startdate;
    QDate enddate;
    QDateTime creationtime;
    QTime timeinoneday;

    QMap<QDate,counttime> timedata;


    QString gettaskname(void){return taskname;};
    void changestate(int i){
        taskstate = i;
    }

    taskdata(){
        taskname = "name",
        taskdetail = "detail",
        taskid = 0,
        startdate = {2023,11,1},
        enddate={2023,11,1};
        creationtime = QDateTime::currentDateTime();
        taskstate = 0;
        timeinoneday = {1,0,0,0};
    }
    void appendtime(counttime n){
        timedata.insert(QDate::currentDate(),n);
    }
};

#endif // TASKDATA_H
