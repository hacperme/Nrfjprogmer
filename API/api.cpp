#include "api.h"

API::API(QObject *parent) : QObject(parent)
{
    nrfjprog_path = find_nrf_path();

}

void API::set_nrf_path(QString path)
{
    nrfjprog_path = path;
}

/**
 * @brief API::get_nrf_path
 * @return
 */
QString API::get_nrf_path()
{
    return nrfjprog_path;
}

/**
 * @brief API::nrfjprog_recover
 * @param family
 * @return
 */
int API::nrfjprog_recover(QString family="UNKNOWN")
{
    int ret;
    QString output;
    QStringList args;
    args << "--recover" << "-f" << family;
    ret = run_command(nrfjprog_path, args, output);
    qDebug()<<output<<ret;
    return ret;

}

/**
 * @brief API::nrfjprog_reset
 * Performs a soft reset by setting the SysResetReq bit of
 *the AIRCR register of the core.
 *
 * @param family
 * @return
 */
int API::nrfjprog_reset(QString family="UNKNOWN")
{
    int ret;
    QString output;
    QStringList args;
    args << "-r" << "-f" << family;
    ret = run_command(nrfjprog_path, args, output);
    qDebug()<<output<<ret;
    return ret;
}

/**
 * @brief API::nrfjprog_program
 * @param hex
 * @param family
 * @param verify
 * @param reset
 * @param sectorerase
 * @param sectoranduicrerase
 * @param chiperase
 * @param qspichiperase
 * @param qspisectorerase
 * @return
 */
int API::nrfjprog_program(QString hex, QString family="UNKNOWN", bool verify=false,
                          bool reset=false, bool sectorerase=false,
                          bool sectoranduicrerase=false, bool chiperase=false,
                          bool qspichiperase=false, bool qspisectorerase=false)
{
    int ret;
    QString output;
    QStringList args;
    args << "--program" << hex << "-f" << family;
    if(verify)
        args << "--verify";
    if(reset)
        args << "--reset";

    if(sectorerase)
        args << "--sectorerase";
    if(sectoranduicrerase)
        args << "--sectoranduicrerase";
    if(chiperase)
        args << "--chiperase";
    if(qspisectorerase)
        args << "--qspisectorerase";
    if(qspichiperase)
        args << "--qspichiperase";

    ret = run_command(nrfjprog_path, args, output);
    qDebug()<<output<<ret;
    return ret;
}

/**
 * @brief API::nrfjprog_eraseall
 * @param family
 * @param qspieraseall
 * @return
 */

int API::nrfjprog_eraseall(QString family="UNKNOWN", bool qspieraseall=false)
{
    int ret;
    QString output;
    QStringList args;
    args << "-e" << "-f" << family;
    if(qspieraseall)
        args << "--qspieraseall";
    ret = run_command(nrfjprog_path, args, output);
    qDebug()<<output<<ret;
    return ret;
}

/**
 * @brief API::nrfjprog_memwr
 * @param addr
 * @param value
 * @param family
 * @param verify
 * @return
 */
int API::nrfjprog_memwr(QString addr, QString value,
                        QString family="UNKNOWN", bool verify=false)
{
    int ret;
    QString output;
    QStringList args;
    args << "--memwr" << addr << value << "-f" << family;
    if(verify)
        args << "--verify";
    ret = run_command(nrfjprog_path, args, output);
    qDebug()<<output<<ret;
    return ret;
}

/**
 * @brief API::nrfjprog_memrd
 * @param addr
 * @param word_size
 * @param family
 * @return
 */
int API::nrfjprog_memrd(QString addr, QString word_size="8", QString family="UNKNOWN")
{
    int ret;
    QString output;
    QStringList args;
    args << "--memrd" << addr << "-f" << family;
    args << "--n" << word_size;
    ret = run_command(nrfjprog_path, args, output);
    qDebug()<<output<<ret;
    return ret;
}




QString API::find_nrf_path()
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


