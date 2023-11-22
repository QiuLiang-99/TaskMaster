#ifndef NEWTASK_H
#define NEWTASK_H

#include <QWidget>

#include "taskdata.h"

namespace Ui {
class newtask;
}

class newtask : public QWidget
{
    Q_OBJECT

public:
    explicit newtask(QWidget *parent = nullptr);
    ~newtask();
    void settaskid(int);
    QStringList taskname;


signals:
    void newtaskcreated(taskdata);

private slots:
    void on_cancelbutton_clicked();

    void on_addButton_clicked();

private:
    Ui::newtask *ui;
    int taskid;
};

#endif // NEWTASK_H
