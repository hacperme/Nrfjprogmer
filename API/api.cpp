#include "api.h"

API::API(QObject *parent) : QObject(parent)
{
    nrfjprog_path = get_nrf_path();

}

int API::nrfjprog_recover()
{
    int ret;
    QString output;
    QStringList args;
    args << "--recover";
    ret = run_command(nrfjprog_path, args, output);
    qDebug()<<output<<ret;
    return ret;

}

QString API::get_nrf_path()
{
    QString program = "cmd";
    QStringList arguments;
    int ret;
    arguments << "/c" << "where nrfjprog";
    QString path;
    ret = run_command(program, arguments, path);
    if(ret == 0)
        return path;
    return "";

}

//void testfunc(void){
////    QObject *parent;
//    QString program = "C:\\Program Files (x86)\\Nordic Semiconductor\\nrf5x\\bin\\nrfjprog.exe";
//    QStringList arguments;
//    arguments << "-v";

//    QProcess *myProcess = new QProcess(NULL);
//    myProcess->start(program, arguments);
//    myProcess->waitForStarted();
//    myProcess->waitForFinished();

//    QString strTemp=QString::fromLocal8Bit(myProcess->readAllStandardOutput());
//    qDebug()<<strTemp<<myProcess->exitCode();

//}


int API::run_command(QString cmd, QStringList arg, QString &output)
{
    QProcess *p = new QProcess(0);
    int ret;
    p->start(cmd, arg);
    if(!p->waitForStarted(-1))
        return -1;
//    p->waitForReadyRead()
    p->waitForFinished();
    ret = p->exitCode();
    if(ret == 0)
        output = QString::fromLocal8Bit(p->readAllStandardOutput()).remove(-2,2);   //去除 /r/n
//    qDebug()<<ret;
    p->close();
//    delete p;
    return ret;

}


