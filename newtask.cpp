#include "newtask.h"
#include "ui_newtask.h"

newtask::newtask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newtask)
{
    ui->setupUi(this);
    setWindowTitle("新建项目");
    ui->remindlabel->hide();
    QDateTime now = QDateTime::currentDateTime();
    ui->startdate->setDate(now.date());
    ui->enddate->setDate(now.date());
    ui->remindtime->setTime(now.time());

    //ui->w1->setStyleSheet("border-radius:5px;");
    //qDebug()<<ui->statebuttonGroup->checkedId();
    ui->statebuttonGroup->setId(ui->state0,0);
    ui->statebuttonGroup->setId(ui->state1,1);
    ui->statebuttonGroup->setId(ui->state2,2);
}

newtask::~newtask()
{
    delete ui;
}

void newtask::settaskid(int n)
{
    taskid = n;
}

void newtask::on_cancelbutton_clicked()
{
    newtask::close();
}


void newtask::on_addButton_clicked()
{
    if((ui->tasknameEdit->text()).isEmpty()){
        ui->tasknameEdit->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}");
        ui->remindlabel->setText("任务名不能为空！");
        ui->remindlabel->show();
        ui->remindlabel->adjustSize();
        return;
        }
    if(taskname.contains(ui->tasknameEdit->text())){
        ui->tasknameEdit->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}");
        ui->remindlabel->setText("此任务名已经存在!");
        ui->remindlabel->show();
        ui->remindlabel->adjustSize();
        return;
        }
        taskdata n;
        n.taskid = taskid;
        n.taskname = ui->tasknameEdit->text();
        n.taskdetail = ui->taskdetailEdit->toPlainText();
        n.startdate = ui->startdate->date();
        n.enddate = ui->enddate->date();
        n.taskstate = ui->statebuttonGroup->checkedId();
        n.timeinoneday={ui->hourspinBox->value(),ui->minutespinBox->value(),0,0};
        qDebug()<<n.timeinoneday;
        emit newtaskcreated(n);
        newtask::close();
}



