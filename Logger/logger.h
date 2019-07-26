#ifndef LOGGER_H
#define LOGGER_H

#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>
#include <QDateTime>
#include <QMutex>
#include <QFile>
#include <QTextStream>

// void myMessageHandler(QtMsgType, const QMessageLogContext &, const QString &);
//typedef QtMessageHandler

void defaultMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

class Logger
{
public:

    Logger();

    void config(QtMessageHandler = defaultMessageHandler);
    void reset();


signals:
    void loggs_ready();


private:

};



#endif // LOGGER_H
