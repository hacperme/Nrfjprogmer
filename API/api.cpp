#include "api.h"

API::API(QObject *parent) : QObject(parent)
{
    nrfjprog_path = find_nrf_path();

}

void API::nrfjprog_set_path(QString path)
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
int API::nrfjprog_recover(QString family)
{
    int ret;
//    QString output;
    QStringList args;
    args << "--recover" << "-f" << family;
    ret = run_command(nrfjprog_path, args);
//    qDebug()<<output<<ret;
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
int API::nrfjprog_reset(QString family)
{
    int ret;
//    QString output;
    QStringList args;
    args << "-r" << "-f" << family;
    ret = run_command(nrfjprog_path, args);
//    qDebug()<<output<<ret;
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
int API::nrfjprog_program(QString hex, QString family, bool verify,
                          bool reset, bool sectorerase,
                          bool sectoranduicrerase, bool chiperase,
                          bool qspichiperase, bool qspisectorerase)
{
    int ret;
//    QString output;
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

    ret = run_command(nrfjprog_path, args);
//    qDebug()<<output<<ret;
    return ret;
}

/**
 * @brief API::nrfjprog_eraseall
 * @param family
 * @param qspieraseall
 * @return
 */

int API::nrfjprog_eraseall(QString family, bool qspieraseall)
{
    int ret;
//    QString output;
    QStringList args;
    args << "-e" << "-f" << family;
    if(qspieraseall)
        args << "--qspieraseall";
    ret = run_command(nrfjprog_path, args);
//    qDebug()<<output<<ret;
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
int API::nrfjprog_memwr(QString addr, QString value, QString family, bool verify)
{
    int ret;
//    QString output;
    QStringList args;
    args << "--memwr" << addr << "--val" << value << "-f" << family;
    if(verify)
        args << "--verify";
    ret = run_command(nrfjprog_path, args);
//    qDebug()<<output<<ret;
    return ret;
}

/**
 * @brief API::nrfjprog_memrd
 * @param addr
 * @param bytes
 * @param family
 * @return
 */
int API::nrfjprog_memrd(QString addr, QString bytes, QString family)
{
    int ret;
    QString output;
    QStringList args;
    args << "--memrd" << addr << "-f" << family;
    args << "--n" << bytes;
    ret = run_command(nrfjprog_path, args);
//    qDebug()<<output<<ret;
    return ret;
}


/**
 * @brief API::nrfjprog_eraseuicr
 * @param family
 * @return
 */
int API::nrfjprog_eraseuicr(QString family)
{
    int ret;
    QString output;
    QStringList args;
    args << "--eraseuicr" << "-f" << family;
    ret = run_command(nrfjprog_path, args);
//    qDebug()<<output<<ret;
    return ret;
}

int API::nrfjprog_erasepage(QString addr_start, QString addr_end, QString family)
{
    int ret;
    QString output;
    QStringList args;
    args << "--erasepage" << addr_start + "-" + addr_end << "-f" << family;
    ret = run_command(nrfjprog_path, args);
//    qDebug()<<output<<ret;
    return ret;
}

int API::nrfjprog_rbp(QString level, QString family)
{
    int ret;
//    QString output;
    QStringList args;
    args << "--rbp" << level << "-f" << family;
    ret = run_command(nrfjprog_path, args);
//    qDebug()<<logs<<ret;
    return ret;
}

int API::nrfjprog_ids(QString &serial_id ,QString family)
{
    int ret;
//    QString output;
    QStringList args;
    args << "--ids" << "-f" << family;
    ret = run_command(nrfjprog_path, args);
    serial_id =logs;
//    qDebug()<<serial_id<<ret;
    return ret;
}

int API::nrfjprog_readcode(QString path, QString family,
                           bool readuicr, bool readram, bool readqspi)
{
    int ret;
//    QString output;
    QStringList args;
    args << "--readcode" << path << "-f" << family;
    if(readuicr)
        args<<"--readuicr";
    if(readram)
        args<<"--readram";
    if(readqspi)
        args<<"--readqspi";

    ret = run_command(nrfjprog_path, args);
//    qDebug()<<logs<<ret;
    return ret;
}




QString API::find_nrf_path()
{
    QString program = "cmd";
    QStringList arguments;
    int ret;
    arguments << "/c" << "where nrfjprog";
    QString path;
    ret = run_command(program, arguments);
    if(ret == 0)
        path = logs.remove(-2,2);   //去除 /r/n
        return path;
    return "";

}



int API::run_command(QString cmd, QStringList arg)
{
    QProcess *p = new QProcess(0);
    int ret;
    p->start(cmd, arg);
    if(!p->waitForStarted(-1))
        return -1;
//    p->waitForReadyRead()
    p->waitForFinished();
    ret = p->exitCode();
    logs = QString::fromLocal8Bit(p->readAllStandardOutput());
    emit logs_is_ready();
    p->close();
    return ret;

}


