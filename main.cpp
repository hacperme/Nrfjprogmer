#include <QApplication>
#include <QProcess>
#include <QDebug>


#include "API/api.h"
#include "UI/mainwindow.h"
#include "Tests/test.h"




int main(int argc, char *argv[])
{   

    QApplication a(argc, argv);

#ifdef RUN_TEST
    test_all();
#else

    MainWindow w;
    w.show();
    return a.exec();
#endif

    return 0;
}


