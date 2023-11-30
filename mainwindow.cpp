#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("TaskMasterv0.1");
    loaddatatoqlist(); //读取保存的task
    openlist();//刷新任务清单
    currentDate = QDate::currentDate(); // 初始化为当前日期
    ui->taskCalendar->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//自动适应行高

    openCalendar(currentDate); // 显示当前月份的日历

    ui->functionbuttonGroup->setId(ui->taskButton,0);
    ui->functionbuttonGroup->setId(ui->listButton,1);
    ui->functionbuttonGroup->setId(ui->calendarButton,2);
    ui->functionbuttonGroup->setId(ui->noteButton,3);
    ui->functionbuttonGroup->setId(ui->classificationButton,4);
    ui->functionbuttonGroup->setId(ui->settingButton,5);
    connect(ui->functionbuttonGroup, &QButtonGroup::buttonClicked,this, [=]() {
        ui->stackedWidget->setCurrentIndex(ui->functionbuttonGroup->checkedId());
        if(2 == ui->functionbuttonGroup->checkedId()){openCalendar(currentDate);}
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
    for (QVector<taskdata>::iterator it = taskqlist.begin(); it != taskqlist.end(); ++it) {
        QJsonObject taskitem;
        taskdata &n = *it;
        taskitem.insert("taskname",n.taskname);
        taskitem.insert("taskdetail",n.taskdetail);
        taskitem.insert("taskstartdate",(n.startdate).toString("yyyy-MM-dd"));
        taskitem.insert("taskenddate",(n.enddate).toString("yyyy-MM-dd"));
        taskitem.insert("taskid",n.taskid);
        taskitem.insert("taskstate",n.taskstate);
        taskitem.insert("creationtime",(n.creationtime).toString("yyyy-MM-dd hh:mm:ss"));
        taskitem.insert("timeinoneday",(n.timeinoneday).toString("hh:mm:ss:zzz"));
        // 手动构建 JSON 对象保存 QMap<QDate, counttime>
        QJsonObject timedataObj;
        for (auto timedataIt = n.timedata.begin(); timedataIt != n.timedata.end(); ++timedataIt) {
            QDate date = timedataIt.key();
            const counttime& ct = timedataIt.value();

            QJsonObject counttimeObj;
            counttimeObj.insert("start", ct.start.toString("hh:mm:ss"));
            counttimeObj.insert("end", ct.end.toString("hh:mm:ss"));
            counttimeObj.insert("total", ct.total.toString("hh:mm:ss"));

            timedataObj.insert(date.toString("yyyy-MM-dd"), counttimeObj);
        }
        taskitem.insert("timedata", timedataObj);
        task.append(taskitem);
    }
    QJsonDocument doc(task);
    QByteArray json = doc.toJson();
    QFile file(filePath);
    file.open(QFile::WriteOnly);
    file.write(json);
    file.close();
}
void MainWindow::loaddatatoqlist()                                                          //读取数据
{
    QFile file(filePath);
    file.open(QFile::ReadOnly);
    QByteArray all = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(all);
    QJsonArray arr = doc.array();
    taskcount = arr.size();
    for (int i = 0; i < taskcount; i++) {
        QJsonValue value = arr.at(i);
        QJsonObject obj = value.toObject();
        taskdata o;
        o.taskname = (obj.value("taskname")).toString();
        o.taskdetail = (obj.value("taskdetail")).toString();
        o.startdate = QDate::fromString((obj.value("taskstartdate")).toString("yyyy-MM-dd"), "yyyy-MM-dd");
        o.enddate = QDate::fromString((obj.value("taskenddate")).toString("yyyy-MM-dd"), "yyyy-MM-dd");
        o.taskid = (obj.value("taskdid")).toInt();
        o.taskstate = (obj.value("taskstate")).toInt();
        o.creationtime = QDateTime::fromString((obj.value("creationtime")).toString("yyyy-MM-dd hh:mm:ss"), "yyyy-MM-dd hh:mm:ss");
        o.timeinoneday = QTime::fromString((obj.value("timeinoneday")).toString("hh:mm:ss"), "hh:mm:ss:zzz");

        // 处理timedata
        QVariantMap variantMap = (obj.value("timedata")).toVariant().toMap();
        QMap<QDate, counttime> timedata;
        for (auto it = variantMap.begin(); it != variantMap.end(); ++it) {
            QDate date = QDate::fromString(it.key(), "yyyy-MM-dd");

            QVariantMap counttimeMap = it.value().toMap();
            counttime ct;
            ct.start = counttimeMap.value("start").toTime();
            ct.end = counttimeMap.value("end").toTime();
            ct.total = counttimeMap.value("total").toTime();

            timedata.insert(date, ct);
        }
        o.timedata = timedata;

        taskqlist.append(o);
    }

}

void MainWindow::addtasklistitem(QString str)                                           //添加listview的item的函数
{
    QStandardItem *newitem = new QStandardItem(str);
    taskdata n;
    for (QMutableVectorIterator<taskdata> it(taskqlist);it.hasNext();) {
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
void MainWindow::openlist(){                                                            //初始化listview
    taskmodel->clear();
    QStringList headers = {"未开始", "进行中", "已完成"};
    taskmodel->setHorizontalHeaderLabels(headers);
    ui->tasklist->setModel(taskmodel);
    QVector<taskdata>::iterator it;
    for (it = taskqlist.begin(); it != taskqlist.end(); ++it) {
    const taskdata &n = *it;
    thetaskStrList << n.taskname;
    QStandardItem *newitem = new QStandardItem(n.taskname);
    int column = n.taskstate; // 你想要的列
    for (int row = 0; row <= taskmodel->rowCount(); ++row){
            // 检查这个位置是否已经有项目
            if (!taskmodel->item(row, column)) {
            // 如果这个位置没有项目，那么在这个位置设置新的项目
            taskmodel->setItem(row, column, newitem);
            break;
            }
    }
    }
}

void MainWindow::openCalendar(QDate date) {                                                     //初始化日历
    int year, week;
    week = date.weekNumber(&year); // 获取年份和周数
    QString dateString = QString("%1年%2月 第%3周").arg(year).arg(date.month()).arg(week);
    ui->datenow->setText(dateString);

    QStandardItemModel *model = new QStandardItemModel(2, 7, this); // 6 rows, 7 columns
    ui->taskCalendar->setModel(model);

    QStringList headers = {"星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期日"};
    QFont font;
    font.setBold(true);
    QBrush brush(Qt::red);

    for (int i = 0; i < headers.size(); ++i) {
    QStandardItem *item = new QStandardItem(headers[i]);
    if (i >= 5) { // 周末
            item->setFont(font);
            item->setForeground(brush);
    }
    model->setHorizontalHeaderItem(i, item);
    }
    int dayOfWeek = date.dayOfWeek();
    // 计算当前日期是本周的第几天
    // 填充本周的日期
    for (int i = 0; i < 7; ++i) {
    QDate currentDate = date.addDays(i - dayOfWeek + 1);
    QStandardItem *item;
    // 检查日期是否超过当前月份的天数
    item = new QStandardItem(QString::number(currentDate.day()));
    model->setItem(0, i, item);
    // 检查每个Data对象
    int row = 1;
    for (QVector<taskdata>::iterator it = taskqlist.begin(); it != taskqlist.end(); ++it) {
            const taskdata &n = *it;
            if (isDateInRange(n.startdate, n.enddate, currentDate)) {
            QStandardItem *valueItem = new QStandardItem(n.taskname);
            model->setItem(row, i, valueItem); // 在匹配的Data对象的下一行添加一个新项目
            row++;
            }
    }
    }


}

void MainWindow::on_nextMonthButton_clicked() {
    currentDate = currentDate.addMonths(1); // 将日期增加一个月
    openCalendar(currentDate); // 显示新的月份的日历
}

void MainWindow::on_lastMonthButton_clicked(){
    currentDate = currentDate.addMonths(-1); // 将日期增加一个月
    openCalendar(currentDate); // 显示新的月份的日历
}
void MainWindow::on_nextWeekButton_clicked()
{
    currentDate = currentDate.addDays(7); // 将日期增加一个月
    openCalendar(currentDate); // 显示新的月份的日历
}


void MainWindow::on_lastWeekButton_clicked()
{
    currentDate = currentDate.addDays(-7); // 将日期增加一个月
    openCalendar(currentDate); // 显示新的月份的日历
}

void MainWindow::on_addButton_clicked()                                             //新建一个task界面
{
    n = new newtask;
    n->show();
    n->settaskid(taskcount);
    n->taskname = thetaskStrList;
    connect(n, &newtask::newtaskcreated, this, &MainWindow::addatask);

    n->setAttribute(Qt::WA_DeleteOnClose);
}
void MainWindow::on_startButton_clicked()                                           //开始一个task界面
{
    d  = new doingtask;
    d->show();
    taskdata n;
    for (QMutableVectorIterator<taskdata> it(taskqlist);it.hasNext();) {
        const taskdata &currentTask = it.next();
        if (currentTask.taskname == *name) {
            n = currentTask;
            break;
        }
    }
    d->settaskname(n.taskname);
    d->settaskdetail(n.taskdetail);
    d->setWindowTitle("任务" + n.taskname);
    d->settimeinday(n.timeinoneday);

    connect(d, &doingtask::thistimedone, this, &MainWindow::onetaskdone);
    d->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
}
void MainWindow::on_deleteButton_clicked()                                              //删除一个taskitem
{
    for (QMutableVectorIterator<taskdata> it(taskqlist);it.hasNext();) {
        const taskdata &currentTask = it.next();
        if (currentTask.taskname == *name) {
            it.remove();
            savedata();
            openlist();
            break;
        }
    }
}
void MainWindow::addatask(taskdata newtask){                                            //来自newtask的槽函数，新建task并保存
    taskqlist.append(newtask);
    addtasklistitem(newtask.gettaskname());
    taskcount++;
}

void MainWindow::onetaskdone(counttime time)                                                 //来自doingtask的槽函数，保存时间
{
    this->show();
    taskdata n;
    for (QMutableVectorIterator<taskdata> it(taskqlist);it.hasNext();) {
        taskdata &currentTask = it.next();
        if (currentTask.taskname == *name) {
            currentTask.appendtime(time);
            break;
        }
    }
}

void MainWindow::on_tasklist_customContextMenuRequested(const QPoint &pos)            //tableview右键菜单
{
    QMenu menu;
    QMenu trans;
    //添加菜单项，指定图标、名称、响应函数


    //在鼠标位置显示
    if(name->isEmpty()){
        menu.addAction(QStringLiteral("新建"),this,SLOT(on_addButton_clicked()));}
    else{
        menu.addAction(QStringLiteral("开始"),this,SLOT(on_startButton_clicked()));
        menu.addAction(QStringLiteral("删除"),this,SLOT(on_deleteButton_clicked()));

    trans.setTitle("转为");
    for (QVector<taskdata>::iterator it = taskqlist.begin(); it != taskqlist.end(); ++it) {
        taskdata n = *it;
        if(n.taskname == *name){
            if (0 == n.taskstate) {
                trans.addAction(QStringLiteral("进行中"),this,[=]{
                it->changestate(1);
                    openlist();
            });
                trans.addAction(QStringLiteral("已完成"),this,[=]{
                it->changestate(2);
                    openlist();
                });}
                else if (1 == n.taskstate) {
                trans.addAction(QStringLiteral("未开始"),this,[=]{
                it->changestate(0);
                    openlist();
            });
                trans.addAction(QStringLiteral("已完成"),this,[=]{
                it->changestate(2);
                    openlist();
                });}
                else if (2 == n.taskstate) {
                trans.addAction(QStringLiteral("未开始"),this,[=]{
                it->changestate(0);
                    openlist();
            });
                trans.addAction(QStringLiteral("进行中"),this,[=]{
                it->changestate(1);
                    openlist();
            });
        }
                menu.addMenu(&trans);
        break;
    }
    }
    };



    menu.exec(QCursor::pos());
}


void MainWindow::on_tasklist_pressed(const QModelIndex &index)                          //当你选中一个item时（包括左右键）
{
    ui->startButton->show();
    *name = ui->tasklist->model()->data(index).toString();
    for (QVector<taskdata>::iterator it = taskqlist.begin(); it != taskqlist.end(); ++it) {
    const taskdata &n = *it;
    if (n.taskname == *name) {
        ui->name_1->setText("项目名称："+n.taskname);
        ui->timeinday_1->setText("今日时长："+n.timeinoneday.toString());
        ui->remaintime_1->setText("剩余时长：");
        ui->totaltime_1->setText("总时长：");

    }
    }

}


void MainWindow::on_tasklist_doubleClicked(const QModelIndex &index)                //双击item函数

{
    on_startButton_clicked();
}



