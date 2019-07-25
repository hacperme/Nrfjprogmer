#ifndef API_H
#define API_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QDebug>


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
    void logs_is_ready(void);

public slots:

private:

    QString find_nrf_path(void);
    int run_command(QString cmd, QStringList arg);
    QString nrfjprog_path;

};

#endif // API_H
