#include <QApplication>


#include "api.h"



/**
 * @brief API::API
 * API 构造函数
 * @param parent
 */
API::API(QObject *parent) : QObject(parent)
{
    p = new QProcess(this);
    nrfjprog_path = find_nrf_path();

}

/**
 * @brief API::nrfjprog_set_path
 * 设置 nrfjprog 程序的绝对路径
 * @param path  nrfjprog 程序的绝对路径
 */
void API::nrfjprog_set_path(QString path)
{
    nrfjprog_path = path;
}

/**
 * @brief API::get_nrf_path
 * 读取当前 nrfjprog 程序的绝对路径
 * @return  nrfjprog 程序的绝对路径
 */
QString API::get_nrf_path()
{
    return nrfjprog_path;
}

/**
 * @brief API::nrfjprog_recover
 * Erases all user flash memory and disables the readback
 * protection mechanism if enabled.
 * @param Selects the device family for the operation.
 * family Valid argument options are NRF51, NRF52, and UNKNOWN.
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
 * the AIRCR register of the core.
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
int API::nrfjprog_program(QString hex, bool verify, bool reset, bool sectorerase,
                          bool sectoranduicrerase, bool chiperase,
                          bool qspichiperase, bool qspisectorerase, QString family)
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
 * Erases all user available program flash memory and the UICR page.
 * @param qspieraseall
 * @param family
 * @return
 */
int API::nrfjprog_eraseall(bool qspieraseall, QString family)
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
 * Writes to the provided address in memory with help of
 * the NVM Controller or, if your device is equipped with
 * a QSPI peripheral and the address to write belongs to
 * the XIP region, with the help of the QSPI peripheral to
 * an external memory device.
 * @param addr
 * @param value
 * @param verify
 * @param family
 * @return
 */
int API::nrfjprog_memwr(QString addr, QString value,bool verify, QString family)
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
 * Reads n bytes from the provided address. If width is
 * not given, 32-bit words are read if addr is word aligned,
 * 16-bit words if addr is half word aligned, and 8-bitwords otherwise.
 * If n is not given, one word of size width is read.
 * The address and n must be aligned to the width parameter.
 * The maximum number of bytesthat can be read is 1 MB.
 * The width must be 8, 16, or 32.
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
 * Erases the UICR page.
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

/**
 * @brief API::nrfjprog_erasepage
 * Erases the flash pages starting at the given start address
 * and ending at the given end address (not included in the erase).
 *  If no end address is given, only one flash page will be erased.
 * @param addr_start
 * @param addr_end
 * @param family
 * @return
 */
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

/**
 * @brief API::nrfjprog_rbp
 * Enables the readback protection mechanism.
 * Valid argument options are CR0 and ALL.
 * @param level
 * @param family
 * @return
 */
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

/**
 * @brief API::nrfjprog_ids
 * Displays the serial numbers of all the debuggers
 * connected to the computer.
 * @param serial_id
 * @param family
 * @return
 */
int API::nrfjprog_ids(QString &serial_id ,QString family)
{
    int ret;
    QStringList args;
    QProcess pro;
    QString output;
    args << "--ids" << "-f" << family;
    pro.start(nrfjprog_path, args);
    pro.waitForFinished(-1);
    ret = pro.exitCode();
//    if(ret == 0)
    output = pro.readAllStandardOutput();
    if(output == "")
        serial_id = "设备未连接\n";
    else
        serial_id = output;
    handle_error(ret);
    return ret;
}

/**
 * @brief API::nrfjprog_readcode
 * Reads the device flash
 * and stores it in the given file path.
 * @param path
 * @param readuicr
 * @param readram
 * @param readqspi
 * @param family
 * @return
 */
int API::nrfjprog_readcode(QString path, bool readuicr,
                           bool readram, bool readqspi, QString family)
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




/**
 * @brief API::find_nrf_path
 * 调用 cmd 命令查找 nrfjprog 安装位置
 * @return
 */
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


/**
 * @brief API::run_command
 * 创建新进程 执行 程序
 * @param cmd   程序路径
 * @param arg   命令行参数
 * @return
 */
int API::run_command(QString cmd, QStringList arg)
{
    int ret;

#if 0
    if(ret == 0){
        logs = QString::fromLocal8Bit(p->readAllStandardOutput());
    }
    else {
        logs = QString::fromLocal8Bit(p->readAllStandardError());
    }

    emit logs_is_ready();
#endif


#ifdef RUN_TEST
    p->start(cmd, arg);
    p->waitForFinished();
    ret = p->exitCode();
    logs = QString::fromLocal8Bit(p->readAll());
    qDebug()<<"run_comm ret code:"<<cmd<<ret<<logs;
#else
    QObject::connect(p,SIGNAL(readyReadStandardOutput()), this, SLOT(update_info_logs()));

    QObject::connect(p,SIGNAL(readyReadStandardError()), this, SLOT(update_error_logs()));

    p->start(cmd, arg);
    while (!p->waitForFinished(3000)) {
        QApplication::processEvents();
    }
    ret = p->exitCode();

#endif

    p->close();
    handle_error(ret);

    return ret;
}

/**
 * @brief API::handle_error
 * 处理 nrfjprog 运行的错误
 * @param error_no
 */
void API::handle_error(int error_no)
{
    QString title = "未知错误";
    QString message;
//    qDebug()<<NoLogWarning;
    switch (error_no) {
    case NoDebuggersError:
        title = "NoDebuggersError";
        message = "There are no debuggers connected to the PC.";
        break;
    case -1:
        title = "出错了";
        message = "不能启动 Nrfjprog 程序";
        break;
    case VerifyError:
        title = "VerifyError";
        message = "The write verify operation failed.";
        break;
    case UnavailableOperationBecauseProtectionError:
        title = "UnavailableOperationBecauseProtectionError";
        message = "The operation attempted cannot be performed because either the main-ap or the ctrl-ap is not available.";
        break;
    case NoWritePermissionError:
        title = "NoWritePermissionError";
        message = "Unable to create file in the current working directory.";
        break;

    case UnavailableOperationInFamilyError:
        title = "UnavailableOperationInFamilyError";
        message = "The operation attempted cannot be performed in the device because the feature is lacking in the device family.";
        break;
    case FileNotFoundError :
        title = "FileNotFoundError";
        message = "Unable to find the given file.";
        break;
    default:
        break;
    }

#ifndef RUN_TEST

    if(error_no != 0)
        QMessageBox::critical(0, title, message);

#endif

}




#if 1
void API::update_info_logs()
{
    QString temp;
    temp = QString::fromLocal8Bit(p->readAllStandardOutput());
    if(temp != ""){
        logs = temp;
        emit logs_is_ready();
    }


}


void API::update_error_logs()
{
    QString temp;
    temp = QString::fromLocal8Bit(p->readAllStandardError());
    if(temp != ""){
        logs = temp;
        emit logs_is_ready();
    }
}



#endif



