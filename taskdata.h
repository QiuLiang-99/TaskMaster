#ifndef TASKDATA_H
#define TASKDATA_H

#include <QString>
#include <QDate>
#include <QDataStream>
#include <QFile>
#include <QDebug>

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
};

#endif // TASKDATA_H
