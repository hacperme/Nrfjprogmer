#include "logger.h"

Logger::Logger()
{
    qInstallMessageHandler(0);
}

void Logger::config(QtMessageHandler h)
{
    qInstallMessageHandler(h);
}

void Logger::reset()
{
    qInstallMessageHandler(0);
}



void defaultMessageHandler(QtMsgType type, const QMessageLogContext &context,
                           const QString &msg)
{
    QString text;
        switch(type)
        {
        case QtDebugMsg:
            text = QString("DEBUG");
            break;

        case QtWarningMsg:
            text = QString("WARN");
            break;

        case QtCriticalMsg:
            text = QString("CRITICAL");
            break;

        case QtFatalMsg:
            text = QString("FATAL");
        }

        /* 截取源文件相对位置 */
        QString filepath = QString(context.file);
        int begin = filepath.indexOf('\\', 3);
        filepath = filepath.mid(begin + 1);

        QDateTime now = QDateTime::currentDateTime();
        QString context_info = QString("[%1:%2]").arg(filepath).arg(context.line);
        QString current_date_time = now.toString("hh:mm:ss");
        QString message = QString("%4 %1 %2:%3").arg(text).arg(context_info).arg(msg).arg(current_date_time);

        QString appPath = QApplication::applicationDirPath();
        QString logfile = QString("%1/app/logs/%2.log").arg(appPath).arg(now.toString("yyMMdd"));
        static QMutex mutex;
        mutex.lock();

        QFile file(logfile);
        file.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream text_stream(&file);
        text_stream << message << "\r\n";
        file.flush();
        file.close();

        mutex.unlock();

}
