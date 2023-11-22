#ifndef DOINGTASK_H
#define DOINGTASK_H

#include <QWidget>
#include "timecalculater.h"

namespace Ui {
class doingtask;
}

class doingtask : public QWidget
{
    Q_OBJECT

public:
    explicit doingtask(QWidget *parent = nullptr);
    ~doingtask();

    void settaskname(const QString &taskname);

    void settaskdetail(const QString &taskdetail);
    void settasktime(const QString &tasktime);
private slots:
    void on_quitButton_clicked();


private:
    Ui::doingtask *ui;
};

#endif // DOINGTASK_H
