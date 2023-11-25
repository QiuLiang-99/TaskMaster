#ifndef TIMECALCULATER_H
#define TIMECALCULATER_H

#include <iostream>
#include <ctime>
#include <string>
#include <time.h>
#include <QTime>
#include <QTimer>
#include <sstream>
#include <QDate>
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <QTime>


bool isDateInRange(const QDate &startDate, const QDate &endDate, const QDate &targetDate);

void calculateTimeDifference(const QDateTime &startTime, const QDateTime &endTime);

#endif // TIMECALCULATER_H
