#include "doingtask.h"
#include "./ui_doingtask.h"

doingtask::doingtask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::doingtask)
{
    ui->setupUi(this);


    time.setHMS(0,0,0,0);//设置初始值
    timer = new QTimer(this);//创建一个定时器
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));//手动连接槽函数

}

doingtask::~doingtask()
{
    delete ui;
}
void doingtask::update()
{
    static quint32 time_out=0;
    time_out++;
    time=time.addSecs(1);
    ui->speedtime->setText(time.toString("hh:mm:ss"));
}

void doingtask::startbuttonf(bool &n)
{
    if(n){
        timer->stop();
        n = false;
        ui->startButton->setText("开始");

    }
    else{
        timer->start(1000);
        n = true;
        ui->startButton->setText("暂停");
    }
}
void doingtask::on_quitButton_clicked()
{
    doingtask::close();
}
void doingtask::settaskname(const QString &taskname){
    ui->taskname->setText(taskname);
}
void doingtask::settaskdetail(const QString &taskdetail){
    ui->taskdetail->setText(taskdetail);
}
void doingtask::settasktime(const QString &tasktime){
    ui->tasktime->setText(tasktime);
}

void doingtask::on_startButton_clicked()
{
    startbuttonf(n);
}

