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

private slots:


    void on_button_open_file_clicked();

    void on_button_disable_rbp_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    API *api;

};

#endif // MAINWINDOW_H
