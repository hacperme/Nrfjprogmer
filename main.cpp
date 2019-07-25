#include <QApplication>
#include <QProcess>
#include <QDebug>


#include "API/api.h"
#include "UI/mainwindow.h"
#include "Tests/test.h"


//#define RUN_TEST

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

#ifdef RUN_TEST
    test_all();
#endif

    return a.exec();
}


