#include "doingtask.h"
#include "./ui_doingtask.h"

doingtask::doingtask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::doingtask)
{
    ui->setupUi(this);
}

doingtask::~doingtask()
{
    delete ui;
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

