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

    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&doingtask::timeEnd);

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

void doingtask::timeEnd()
{

    //如果小于0停止计时
    if(sectime < 0)
   {
        m_timer->stop();
        return;
    }
    ui->m_time->setTime(sectime);
    sectime --;

}

void doingtask::startbuttonf(bool &n)
{
    if(n){
        timer->stop();
        m_timer->stop();
        n = false;
        ui->startButton->setText("开始");

    }
    else{
        timer->start(1000);
        m_timer->start(1000);
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

void doingtask::settimeinday(QTime n)
{
    int n_seconds = n.hour()*3600 + n.minute()*60 + n.second() + n.msec()/1000.0;
    qDebug() << n_seconds;
    sectime = n_seconds;
    qDebug() << sectime;
    int hours = static_cast<int>(n_seconds) / 3600;
    n_seconds -= hours * 3600;
    int minutes = static_cast<int>(n_seconds) / 60;
    n_seconds -= minutes * 60;
    int seconds = static_cast<int>(n_seconds);
    QTime a(hours,minutes,seconds,0);
    qDebug()<< a;
    ui->m_time->setTime(sectime);
    ui->m_time->settotaltime(sectime);
}

void doingtask::on_startButton_clicked()
{
    startbuttonf(n);
}

