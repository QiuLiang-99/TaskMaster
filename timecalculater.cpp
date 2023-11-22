#include "timecalculater.h"

#include <QApplication>


using namespace std;

bool isDateInRange(const QDate &startDate, const QDate &endDate, const QDate &targetDate) {
    return targetDate >= startDate && targetDate <= endDate;
}


void calculateTimeDifference(const QDateTime &startTime, const QDateTime &endTime) {
                    qint64 secondsDifference = startTime.secsTo(endTime);
                    qint64 minutesDifference = secondsDifference / 60;
                    qint64 hoursDifference = minutesDifference / 60;

                    qDebug() << "时间差：" << hoursDifference << "小时" << minutesDifference % 60 << "分钟" << secondsDifference % 60 << "秒";
}
