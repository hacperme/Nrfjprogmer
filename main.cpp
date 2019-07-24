#include <QApplication>
#include <QProcess>
#include <QDebug>

#include "API/api.h"
#include "UI/mainwindow.h"


void testfunc(void){
//    QObject *parent;

    API *api = new API;
    QString program = api->nrfjprog_path.remove(-2,2);

//    QString program = "C:\\Program Files (x86)\\Nordic Semiconductor\\nrf5x\\bin\\nrfjprog.exe\r\n";
//    qDebug()<<program.remove(-2,2);
    QStringList arguments;
    arguments << "-h";

    QProcess *myProcess = new QProcess(NULL);
    myProcess->start(program, arguments);
    myProcess->waitForStarted();
    myProcess->waitForFinished();

    QString strTemp=QString::fromLocal8Bit(myProcess->readAllStandardOutput());
    qDebug()<<strTemp<<myProcess->exitCode();
//    qDebug()<< api->nrfjprog_path;

}


int main(int argc, char *argv[])
{
//    testfunc();
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    API *api = new API;
    qDebug() << api->nrfjprog_path;
    api->nrfjprog_recover();

    return 0;//a.exec();
}


