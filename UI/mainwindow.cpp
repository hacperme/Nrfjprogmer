#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QObject>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    api = new API;
    QObject::connect(api, SIGNAL(logs_is_ready()), this, SLOT(update_logs()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::update_logs
 * 更新操作日志信息文本框
 */
void MainWindow::update_logs()
{
//    ui->show_logs->setText(api->logs);
    ui->show_logs->append(api->logs);
}



void MainWindow::on_button_open_file_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,tr("打开文件"), ".",
                                                tr("HEX files (*.hex)"));
    ui->show_file_path->setText(path);
//    qDebug()<<path;
}


void MainWindow::on_button_disable_rbp_clicked()
{
    api->nrfjprog_recover();
}

void MainWindow::on_pushButton_2_clicked()
{
    api->nrfjprog_eraseall();
}
