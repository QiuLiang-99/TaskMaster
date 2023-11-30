#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QStringListModel>
#include <QStringList>
#include <qdatetime.h>
#include <QDebug>
#include <QDataStream>
#include <QFile>
#include <QString>
#include <QList>
#include <QVector>
#include <QStandardItemModel>
#include <QMenu>

#include "newtask.h"
#include "doingtask/doingtask.h"
#include "taskdata.h"
#include "timecalculater.h"
#include "taskCalendar/mydelegate.h"

#include <QJsonDocument>
#include <QJsonobject>
#include <QJsonArray>
#include <QJsonValue>
#include <QStandardPaths>
#include <QDir>

#include <QTextCursor>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString filePath = QDir(documentsPath).filePath("TaskMaster/task.json");
    void savedata();
    void loaddatatoqlist();
    void openlist();
    void openCalendar(QDate date);

    QVector<taskdata> taskqlist;
    QStringList thetaskStrList;//保存初始 StringList
    QStandardItemModel* taskmodel = new QStandardItemModel;//创建数据模型

    //int *id = new int;//the list item haven been chose
    QString *name = new QString;//as up
    int taskcount;
    QDate currentDate;

public slots:
    void addatask(taskdata);
    void onetaskdone(counttime);

protected:
private slots:
    void on_addButton_clicked();
    void on_startButton_clicked();
    void addtasklistitem(QString);
    void on_deleteButton_clicked();
    void on_tasklist_customContextMenuRequested(const QPoint &pos);
    void on_tasklist_pressed(const QModelIndex &index);
    void on_tasklist_doubleClicked(const QModelIndex &index);

    void on_nextMonthButton_clicked();
    void on_lastMonthButton_clicked();

    void on_nextWeekButton_clicked();

    void on_lastWeekButton_clicked();

private:
    Ui::MainWindow *ui;
    newtask *n;
    doingtask *d;
};

#endif // MAINWINDOW_H
