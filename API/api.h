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

    QString nrfjprog_path;

    int nrfjprog_recover();


signals:

public slots:

private:

    QString get_nrf_path(void);
    int run_command(QString cmd, QStringList arg, QString &output);

};

#endif // API_H
