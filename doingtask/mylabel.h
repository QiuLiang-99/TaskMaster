#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QLabel>
#include <QPainter>
#include <QTime>
class MyLabel : public QLabel
{
    Q_OBJECT

public:
    MyLabel(QWidget *parent = Q_NULLPTR);
    ~MyLabel();
public:
    //计时器更新 倒计时
    void setTime(double second);
    void settotaltime(double);
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
    virtual bool event(QEvent *e);

private:
    void drawTimer(QPainter *);//画计时器
private:
    double m_time;//倒计时时间
    double total;//总时间
};
#endif // MYLABEL_H

