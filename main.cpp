#include <QApplication>
#include <QProcess>
#include <QDebug>

#include "API/api.h"
#include "UI/mainwindow.h"
#include "Tests/test.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();


    test_all();

    return 0;//a.exec();
}


