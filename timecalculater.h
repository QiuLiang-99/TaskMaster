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


bool isDateInRange(const QDate &startDateTime, const QDate &endDateTime, const QDate &targetDate);

void calculateTimeDifference(const QDateTime &startTime, const QDateTime &endTime);

#endif // TIMECALCULATER_H
