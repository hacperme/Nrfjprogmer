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

    void set_nrf_path(QString path);
    QString get_nrf_path(void);


    int nrfjprog_recover(QString family);

    int nrfjprog_reset(QString family);

    int nrfjprog_program(QString hex, QString family, bool verify,
                         bool reset, bool sectorerase,
                         bool sectoranduicrerase, bool chiperase,
                         bool qspichiperase, bool qspisectorerase);

    int nrfjprog_eraseall(QString family, bool qspieraseall);

    int nrfjprog_memwr(QString addr, QString value, QString family, bool verify);

    int nrfjprog_memrd(QString addr, QString word_size, QString family);


signals:

public slots:

private:

    QString find_nrf_path(void);
    int run_command(QString cmd, QStringList arg, QString &output);
    QString nrfjprog_path;

};

#endif // API_H
