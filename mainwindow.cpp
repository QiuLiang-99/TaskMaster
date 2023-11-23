#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("TCHLv0.1");
    //读取保存的task
    openlist();
    loaddatatoqlist();

    taskmodel->setHeaderData(0,Qt::Horizontal, "未完成");
    taskmodel->setHeaderData(1,Qt::Horizontal, "进行中");
    taskmodel->setHeaderData(2,Qt::Horizontal, "已完成");
    //taskmodel->setHeaderData(0,Qt::Vertical, "记录一");
    //taskmodel->setHeaderData(1,Qt::Vertical, "记录二");
    //taskmodel->setHeaderData(2,Qt::Vertical, "记录三");
    //taskmodel->setItem(0, 0, new QStandardItem("张三"));
    //taskmodel->setItem(0, 1, new QStandardItem("3"));
    //taskmodel->setItem(0, 2, new QStandardItem("男"));
    ui->tasklist->setModel(taskmodel);

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdata()));
    timer->start(1000);
    //可以只执行一遍，一般放在构造函数
    ui->tasklist->setEditTriggers(QAbstractItemView::NoEditTriggers);//关闭双击可以修改item

    ui->startButton->hide();

    ui->functionbuttonGroup->setId(ui->taskButton,0);
    ui->functionbuttonGroup->setId(ui->listButton,1);
    ui->functionbuttonGroup->setId(ui->calendarButton,2);
    ui->functionbuttonGroup->setId(ui->noteButton,3);
    ui->functionbuttonGroup->setId(ui->classificationButton,4);
    ui->functionbuttonGroup->setId(ui->settingButton,5);
    connect(ui->functionbuttonGroup, &QButtonGroup::buttonClicked,this, [=]() {
        ui->stackedWidget->setCurrentIndex(ui->functionbuttonGroup->checkedId());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    savedata();
}
void MainWindow::savedata()                                                                 //写入数据
{
    QJsonArray task;
    QJsonObject taskitem;
    for (QList<taskdata>::iterator it = taskqlist.begin(); it != taskqlist.end(); ++it) {
        taskdata &n = *it;
        taskitem.insert("taskname",n.taskname);
        taskitem.insert("taskdetail",n.taskdetail);
        //qDebug() << QDate::fromString((n.startdate).toString("yyyy-MM-dd"),"yyyy-MM-dd");
        taskitem.insert("taskstartdate",(n.startdate).toString("yyyy-MM-dd"));
        taskitem.insert("taskenddate",(n.enddate).toString("yyyy-MM-dd"));
        taskitem.insert("taskid",n.taskid);
        taskitem.insert("taskstate",n.taskstate);
        taskitem.insert("creationtime",(n.creationtime).toString("yyyy-MM-dd hh:mm:ss"));
        task.append(taskitem);
    }
    QJsonDocument doc(task);
    QByteArray json = doc.toJson();
    QFile file(filePath);
    file.open(QFile::WriteOnly);
    file.write(json);
    file.close();
}
void MainWindow::loaddatatoqlist()                                               //读取
{
    QFile file(filePath);
    file.open(QFile::ReadOnly);
    QByteArray all = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(all);
    QJsonArray arr = doc.array();
    taskcount = arr.size();
    for(int i = 0;i < taskcount;i++){
        QJsonValue value = arr.at(i);
        QJsonObject obj = value.toObject();
        taskdata o;
        o.taskname = (obj.value("taskname")).toString();
        o.taskdetail = (obj.value("taskdetail")).toString();
        //qDebug() <<(obj.value("taskstartdate")).toString("yyyy-MM-dd")<<"\n";
        o.startdate = QDate::fromString((obj.value("taskstartdate")).toString("yyyy-MM-dd"),"yyyy-MM-dd");
        o.enddate = QDate::fromString((obj.value("taskenddate")).toString("yyyy-MM-dd"),"yyyy-MM-dd");
        o.taskid = (obj.value("taskdid")).toInt();
        o.taskstate = (obj.value("taskstate")).toInt();
        o.creationtime = QDateTime::fromString((obj.value("creationtime")).toString("yyyy-MM-dd hh:mm:ss"),"yyyy-MM-dd hh:mm:ss");
        taskqlist.append(o);
    }

    //qDebug()<< o.taskname <<o.taskdetail<<o.startdate<<o.enddate<<o.taskid;
}
void MainWindow::timerUpdata()                                                      //更新时间
{
    //QFont font("Microsoft YaHei",20,50);
    //QDateTime time = QDateTime::currentDateTime();
    //QString str = "当前时间" + time.toString("yyyy-MM-dd hh:mm:ss dddd");
    //QString str1 = time.toString("yyyy-MM-dd hh:mm:ss");

    //标签的文字被改变一次就要执行一次，一般放在槽函数
    //ui->text->setText(textEdit->toPlainText());//设置文字


    //ui -> text ->setFont(font);
    //this -> ui->text->setText(str);
    //ui->text->adjustSize();//自动调整
    //ui->text->show();
}
void MainWindow::on_tasklist_clicked(const QModelIndex &index)                          //点击listview的函数
{
    ui->startButton->show();
    *name = ui->tasklist->model()->data(index).toString();
    //*id= ui->tasklist->currentIndex().row();
    qDebug() << *name;

}

void MainWindow::addtasklistitem(QString str)                                           //添加listview的item的函数
{
    QStandardItem *newitem = new QStandardItem(str);
    taskdata n;
    for (QMutableListIterator<taskdata> it(taskqlist);it.hasNext();) {
        const taskdata &currentTask = it.next();
        if (currentTask.taskname == str) {
            n = currentTask;
            break;
        }
    }
    int column = n.taskstate;  // 你想要的列
    for (int row = 0; row <= taskmodel->rowCount(); ++row){
        // 检查这个位置是否已经有项目
        if (!taskmodel->item(row, column)) {
            // 如果这个位置没有项目，那么在这个位置设置新的项目
            taskmodel->setItem(row, column, newitem);
            break;
    }
    }
}

void MainWindow::on_deleteButton_clicked()
{

}
void MainWindow::openlist(){                                                            //初始化listview
    QFile file(filePath);
    file.open(QFile::ReadOnly);
    QByteArray all = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(all);
    QJsonArray arr = doc.array();
    taskcount = arr.size();
    qDebug() << taskcount;
    for (int i = 0; i < taskcount; ++i) {
        QJsonValue value = arr.at(i);
        QJsonObject obj = value.toObject();
        thetaskStrList << (obj.value("taskname")).toString();
        QStandardItem *newitem = new QStandardItem((obj.value("taskname")).toString());
        int column = (obj.value("taskstate")).toInt();  // 你想要的列
        for (int row = 0; row <= taskmodel->rowCount(); ++row){
            // 检查这个位置是否已经有项目
            if (!taskmodel->item(row, column)) {
                // 如果这个位置没有项目，那么在这个位置设置新的项目
                taskmodel->setItem(row, column, newitem);
                break;
            }
    }
    file.close();
}
}
void MainWindow::on_addButton_clicked()                                             //新建task界面
{
    n = new newtask;
    n->show();
    n->settaskid(taskcount);
    n->taskname = thetaskStrList;
    connect(n, &newtask::newtaskcreated, this, &MainWindow::addatask);
}
void MainWindow::on_startButton_clicked()                                           //开始task界面
{
    d  = new doingtask;
    d->show();
    taskdata n;
    for (QMutableListIterator<taskdata> it(taskqlist);it.hasNext();) {
        const taskdata &currentTask = it.next();
        if (currentTask.taskname == *name) {
            n = currentTask;
            break;
        }
    }
    d->settaskname(n.taskname);
    d->settaskdetail(n.taskdetail);
    //d->settasktime();
}
void MainWindow::addatask(taskdata newtask){                                            //来自newtask的槽函数，新建task并保存
    taskqlist.append(newtask);
    addtasklistitem(newtask.gettaskname());
    taskcount++;
}
