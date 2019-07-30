#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>

#include <windows.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    api = new API;
    QObject::connect(api, SIGNAL(info_logs_is_ready()), this, SLOT(update_info_logs()));
    QObject::connect(api, SIGNAL(error_logs_is_ready()), this, SLOT(update_error_logs()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::update_logs
 * 更新操作日志信息文本框
 */
void MainWindow::update_info_logs()
{
    QDateTime now = QDateTime::currentDateTime();
    QString current_date_time = QString("[%1]").arg(now.toString("yyyy-MM-dd hh:mm:ss"));

    ui->show_logs->append(current_date_time+"INFO:"+api->logs);
    //    api->logs = "";
}

void MainWindow::update_error_logs()
{
    QDateTime now = QDateTime::currentDateTime();
    QString current_date_time = QString("[%1]").arg(now.toString("yyyy-MM-dd hh:mm:ss"));

    ui->show_logs->append(current_date_time+api->logs);
}


//void MainWindow::update_logs(QString logs)
//{
//    ui->show_logs->append(logs);
//}



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
    if(ui->is_rbp->isChecked()){
        Sleep(500);            //这里可能需要延时，等待 MCU 复位完成，再进行 rbp 操作。
        api->nrfjprog_rbp();
    }
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
    QDateTime now;
    QString current_date_time = QString("[%1]").arg(now.currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    QString ids, nrf_path;
    api->nrfjprog_ids(ids);
    ui->show_logs->append(current_date_time + "INFO:"+"调试器:"+ids);

    nrf_path = api->get_nrf_path();
    current_date_time = QString("[%1]").arg(now.currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->show_logs->append(current_date_time+"INFO:"+"nrfjprog路径:"+nrf_path+"\n");

}

void MainWindow::on_button_clear_logs_clicked()
{
    ui->show_logs->clear();
}

void MainWindow::on_button_save_logs_clicked()
{
    QString save_path = QFileDialog::getSaveFileName(this,tr("保存记录"), ".",
                                             tr("Text files (*.log *.txt)"));
    if(save_path != ""){
        QFile file(save_path);
        file.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream text_stream(&file);
        text_stream <<ui->show_logs->toPlainText();
        file.flush();
        file.close();
    }
    else {

        QMessageBox::warning(this, QString("警告"), QString("保存路径不能为空，记录未保存到文件！"));

    }


}
