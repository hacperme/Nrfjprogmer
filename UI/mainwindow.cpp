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

    ui->show_logs->append(api->logs);
//    api->logs = "";
}


void MainWindow::update_logs(QString logs)
{
    ui->show_logs->append(logs);
}



void MainWindow::on_button_open_file_clicked()
{
    hex_path = QFileDialog::getOpenFileName(this,tr("打开文件"), ".",
                                                tr("HEX files (*.hex)"));
    ui->show_file_path->setText(hex_path);
//    qDebug()<<path;
}


void MainWindow::on_button_disable_rbp_clicked()
{
//    qDebug()<<"into on_button_disable_rbp_clicked() ";

    api->nrfjprog_recover();
}


void MainWindow::on_eraseall_clicked()
{
//    qDebug()<<"into on_eraseall_clicked() ";
    api->nrfjprog_eraseall();
}

void MainWindow::on_program_clicked()
{
//    qDebug()<<"into on_program_clicked ";
    bool verify;
    bool reset;
    verify = ui->is_verify->isChecked();
    reset = ui->is_reset->isChecked();
    api->nrfjprog_recover();
    api->nrfjprog_program(hex_path, verify, reset);
    if(ui->is_rbp->isChecked())
        //这里可能需要延时，等待固件烧写完成再操作。
        api->nrfjprog_rbp();
}



void MainWindow::on_button_readback_clicked()
{
    QString save_path;
    bool include_ram;
    bool include_qspi;
    bool include_icr;

    save_path = QFileDialog::getSaveFileName(this,tr("保存文件"), ".",
                                             tr("HEX files (*.hex)"));

    include_ram = ui->include_ram->isChecked();
    include_icr = ui->include_icr->isChecked();
    include_qspi = ui->include_qspi->isChecked();

    api->nrfjprog_readcode(save_path, include_icr, include_ram, include_qspi);

}

void MainWindow::on_show_logs_textChanged()
{
    ui->show_logs->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
}

void MainWindow::on_button_scan_clicked()
{
    QString ids, nrf_path;
    api->nrfjprog_ids(ids);
    nrf_path = api->get_nrf_path();
    ui->show_logs->append("调试器:"+ids+"nrfjprog路径:"+nrf_path+"\n");

}
