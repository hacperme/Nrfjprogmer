#ifndef API_H
#define API_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>


//#define RUN_TEST

typedef enum {
    Success = 0,
    NrfjprogError = 1,
    NrfjprogOutdatedError = 2,
    MemoryAllocationError = 3,
    InvalidArgumentError = 11,
    InsufficientArgumentsError = 12,
    IncompatibleArgumentsError = 13,
    DuplicatedArgumentsError =14,
    NoOperationError = 15,
    UnavailableOperationBecauseProtectionError = 16,
    UnavailableOperationInFamilyError = 17,
    WrongFamilyForDeviceError = 18,
    UnavailableOperationBecauseMpuConfiguration = 19,
    NrfjprogDllNotFoundError = 20,
    NrfjprogDllLoadFailedError = 21,
    NrfjprogDllFunctionLoadFailedError = 22,
    NrfjprogDllNotImplementedError = 23,
    NrfjprogIniNotFoundError = 25,
    NrfjprogIniCannotBeOpenedError = 26,
    NrfjprogIniFamilyMissingError = 27,
    NrfjprogIniClockspeedMissingError = 28,
    NrfjprogIniQspiIniFileMissingError = 29,
    JLinkARMDllNotFoundError = 30,
    JLinkARMDllInvalidError = 31,
    JLinkARMDllFailedToOpenError = 32,
    JLinkARMDllError = 33,
    JLinkARMDllTooOldError = 34,
    InvalidSerialNumberError = 40,
    NoDebuggersError,
    NotPossibleToConnectError,
    LowVoltageError,
    FileNotFoundError = 51,
    InvalidHexFileError,
    FicrReadError,
    WrongArgumentError,
    VerifyError,
    NoWritePermissionError,
    NVMCOperationError,
    FlashNotErasedError,
    RamIsOffError,
    NoReadPermissionError,
    NoExternalMemoryConfiguredError,
    RecoverFailed = 62,
    NrfjprogQspiIniNotFoundError = 70,
    NrfjprogQspiIniCannotBeOpenedError,
    NrfjprogQspiSyntaxError,
    NrfjprogQspiIniParsingError,
    FicrOperationWarning = 100,
    UnalignedPageEraseWarning,
    NoLogWarning,
    UicrWriteOperationWithoutEraseWarning,
    VeryLongOperationWarning = 104,
    CanNotExecNrfjprog = -1     ///自定义返回值，不能执行程序Nrfjprog
}ErrorCode;




class API : public QObject
{
    Q_OBJECT
public:
    explicit API(QObject *parent = nullptr);

    QString logs;

    void nrfjprog_set_path(QString path);
    QString get_nrf_path(void);


    int nrfjprog_recover(QString family="UNKNOWN");

    int nrfjprog_reset(QString family="UNKNOWN");

    int nrfjprog_program(QString hex, bool verify=false,
                         bool reset=false, bool sectorerase=false,
                         bool sectoranduicrerase=false, bool chiperase=false,
                         bool qspichiperase=false, bool qspisectorerase=false,
                         QString family="UNKNOWN");

    int nrfjprog_eraseall(bool qspieraseall=false, QString family="UNKNOWN");

    int nrfjprog_memwr(QString addr, QString value, bool verify=true,QString family="UNKNOWN");

    int nrfjprog_memrd(QString addr, QString bytes="16", QString family="UNKNOWN");

    int nrfjprog_eraseuicr(QString family="UNKNOWN");

    int nrfjprog_erasepage(QString addr_start, QString addr_end, QString family="UNKNOWN");

    int nrfjprog_rbp(QString level="ALL", QString family="UNKNOWN");

    int nrfjprog_ids(QString &serial_id, QString family="UNKNOWN");

    int nrfjprog_readcode(QString path, bool readuicr=false, bool readram=false,
                          bool readqspi=false, QString family="UNKNOWN");





signals:
    void error_logs_is_ready(void);
    void info_logs_is_ready(void);

public slots:


private:

    QString find_nrf_path(void);
    int run_command(QString cmd, QStringList arg);
    QString nrfjprog_path;
    void handle_error(int error_no);
    QProcess *p;

private slots:

#if 1
    void update_error_logs();
    void update_info_logs();
#endif

};

#endif // API_H
