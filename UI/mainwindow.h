#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../API/api.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void update_logs();
    void update_logs(QString logs);

private slots:


    void on_button_open_file_clicked();

    void on_button_disable_rbp_clicked();

    void on_eraseall_clicked();

    void on_program_clicked();

    void on_button_readback_clicked();

    void on_show_logs_textChanged();

    void on_button_scan_clicked();

private:
    Ui::MainWindow *ui;

    API *api;
    QString hex_path;

};

#endif // MAINWINDOW_H
