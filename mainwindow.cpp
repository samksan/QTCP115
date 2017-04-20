#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database/netnumbers.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTableView>
#include <QSqlQuery>

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include "Analysis/analysiscontrol.h"
#include "Analysis/analysisutils.h"
#include "database/dataall.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化数据库连接
    NetNumbers::initQSQLDatabase();

    // 刷新数据
    DataAll::numbers_all = NetNumbers::getNumbers();

    // 初始化转化字典
    DataAll::InitMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 连接数据库获取号码并利用 Qt 的 Model-View 显示开奖号码
void MainWindow::on_btn_view_number_clicked()
{
    // 获取数据库连接，测试连接是否成功
    QSqlDatabase db = QSqlDatabase::database();
    bool ok = db.open();

    if(ok){
        qDebug() << "connect ok";
    }else{
        qDebug() << "connect failed";
    }

    // Qt Model-View 显示数据库
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("kjh");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("期号"));
    model->setHeaderData(1, Qt::Horizontal, tr("一"));
    model->setHeaderData(2, Qt::Horizontal, tr("二"));
    model->setHeaderData(3, Qt::Horizontal, tr("三"));
    model->setHeaderData(4, Qt::Horizontal, tr("四"));
    model->setHeaderData(5, Qt::Horizontal, tr("五"));

    ui->tableView_number->setModel(model);
    ui->tableView_number->setColumnWidth(0,290);
    ui->tableView_number->setColumnWidth(1,100);
    ui->tableView_number->setColumnWidth(2,100);
    ui->tableView_number->setColumnWidth(3,100);
    ui->tableView_number->setColumnWidth(4,100);
    ui->tableView_number->setColumnWidth(5,100);
}

// 分析历史号码
void MainWindow::on_btn_test_analysis_clicked()
{
    // 参数
    int num_base = ui->comboBox_base->currentText().toInt();
    int num_ana = ui->comboBox_ana->currentText().toInt();
    int num_chart = ui->comboBox_chart->currentText().toInt();

    // 控制分析过程
    AnalysisControl ana;
    ana.start(num_base, num_ana, num_chart);
}

// 从网络获取开奖号码，并保存到数据库
void MainWindow::on_btn_update_number_clicked()
{
    NetNumbers::getHtml("http://ln11x5.icaile.com/?op=dcjb&num=100");
    QMessageBox::information(NULL,tr("号码更新提示"),tr("号码更新成功"),QMessageBox::Ok);

    // 号码 numbers_total => 100 * {期号, n1, n2, n3, n4, n5, n6}
    DataAll::numbers_all = NetNumbers::getNumbers();

    // 判断数据库数据是否小于 100 期
    if (DataAll::numbers_all.length() < 100) {
        qDebug() << "期数总数错误";
        QMessageBox::critical(NULL,
                              tr("错误信息"),
                              tr("号码的期数不正确,可能是数据库数据错误"));
    }
}

// 连接数据库获取号码并利用 Qt 的 Model-View 显示开奖号码
void MainWindow::on_btn_view_number_desc_clicked()
{
    // 获取数据库连接，测试连接是否成功
    QSqlDatabase db = QSqlDatabase::database();
    bool ok = db.open();

    if(ok){
        qDebug() << "connect ok";
    }else{
        qDebug() << "connect failed";
    }

    // Qt Model-View 显示数据库
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("kjh");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0,Qt::DescendingOrder);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("期号"));
    model->setHeaderData(1, Qt::Horizontal, tr("一"));
    model->setHeaderData(2, Qt::Horizontal, tr("二"));
    model->setHeaderData(3, Qt::Horizontal, tr("三"));
    model->setHeaderData(4, Qt::Horizontal, tr("四"));
    model->setHeaderData(5, Qt::Horizontal, tr("五"));

    ui->tableView_number->setModel(model);
    ui->tableView_number->setColumnWidth(0,290);
    ui->tableView_number->setColumnWidth(1,100);
    ui->tableView_number->setColumnWidth(2,100);
    ui->tableView_number->setColumnWidth(3,100);
    ui->tableView_number->setColumnWidth(4,100);
    ui->tableView_number->setColumnWidth(5,100);
}

void MainWindow::on_slider_base_valueChanged(int value)
{
    ui->comboBox_base->setCurrentText(QString::number(value));
}

void MainWindow::on_slider_ana_valueChanged(int value)
{
    ui->comboBox_ana->setCurrentText(QString::number(value));
}

void MainWindow::on_comboBox_base_currentTextChanged(const QString &arg1)
{
    ui->slider_base->setValue(arg1.toInt());
}

void MainWindow::on_comboBox_ana_currentTextChanged(const QString &arg1)
{
    ui->slider_ana->setValue(arg1.toInt());
}

void MainWindow::on_slider_chart_valueChanged(int value)
{
    ui->comboBox_chart->setCurrentText(QString::number(value));
}

void MainWindow::on_comboBox_chart_currentTextChanged(const QString &arg1)
{
    ui->slider_chart->setValue(arg1.toInt());
}

/**
 * @brief MainWindow::on_btn_update_manual_clicked 手动添加开奖号码
 */
void MainWindow::on_btn_update_manual_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
    db.open();
    int n1 = ui->comboBox_n1->currentText().toInt();
    int n2 = ui->comboBox_n2->currentText().toInt();
    int n3 = ui->comboBox_n3->currentText().toInt();
    int n4 = ui->comboBox_n4->currentText().toInt();
    int n5 = ui->comboBox_n5->currentText().toInt();

    if(n1 == n2 || n1 ==n3 || n1 == n4 || n1 == n5 || n2 == n3 || n2==n4 || n2 == n5 || n3 == n4 || n3 == n5 || n4 == n5){
        QMessageBox::warning(NULL,
                             tr("数据输入错误警告"),
                             tr("一组数据里不能包含相同的数字"),
                             QMessageBox::Ok,QMessageBox::Close);
        return;
    }

    QSqlQuery query;
    query.exec("SELECT sn FROM KJH");
    query.last();
    int sn = query.value(0).toInt();
    sn++;
    qDebug() << query.value(0);
    query.prepare("INSERT INTO kjh VALUES(?,?,?,?,?,?)");
    query.addBindValue(sn);
    query.addBindValue(n1);
    query.addBindValue(n2);
    query.addBindValue(n3);
    query.addBindValue(n4);
    query.addBindValue(n5);
    query.exec();

    DataAll::numbers_all = NetNumbers::getNumbers();

    QMessageBox::information(NULL,
                         tr("手动更新成功"),
                         tr("手动更新的号码已经成功写入数据库"),
                         QMessageBox::Ok);
}

/**
 * @brief MainWindow::on_btn_data_refresh_clicked 刷新使用的数据
 */
void MainWindow::on_btn_data_refresh_clicked()
{
    DataAll::numbers_all = NetNumbers::getNumbers();
    qDebug() << "刷新数据完成";
    qDebug() << "检查参数";
    int num_total = DataAll::numbers_all.length();
    int num_base = ui->comboBox_base->currentText().toInt();
    int num_ana = ui->comboBox_ana->currentText().toInt();
    int num_chart = ui->comboBox_chart->currentText().toInt();
    qDebug() << "总期数 = " << QString::number(num_total);

    if (num_total < num_base + num_ana + 1
            || num_ana <= num_chart) {
        QString temp;
        temp.append("总期数: " + QString::number(num_total) + "\n");
        temp.append("基础期数: " + QString::number(num_base) + "\n");
        temp.append("分析期数: " + QString::number(num_ana) + "\n");
        temp.append("图表期数: " + QString::number(num_chart) + "\n");
        temp.append("一: 基础期数和分析期数的和不能大于总期数-1\n");
        temp.append("二: 图表期数不能大于或等于分析期数\n");

        QMessageBox::warning(NULL, tr("错误警告"), temp, QMessageBox::Ok,QMessageBox::Close);
    }

}

/**
 * @brief MainWindow::on_btn_show_chart_clicked 显示分析号码的第1步的结果集
 */
void MainWindow::on_btn_show_chart_clicked()
{
    // DataAll::numbers_ana 写入数据库
    // 获取数据库连接，测试连接是否成功
    QSqlDatabase db = QSqlDatabase::database();
    bool ok = db.open();
    if(!ok){
        QMessageBox::information(NULL, "数据库连接失败", "数据库连接失败!!!", QMessageBox::Ok);
    }

    QSqlQuery query;
    foreach (QVector<int> var, DataAll::numbers_ana) {
        query.prepare("INSERT INTO ana (sn, n1, n2, n3, n4, n5, "
                      "d101, d102 ,d103, d104, d105, d106, d107, d108, d109, d110, d111"
                      "d201, d202, d203, d204, d205, d206, d207, d208, d209, d210, d211"
                      "d301, d302, d303, d304, d305, d306, d307, d308, d309, d310, d311"
                      "d401, d402, d403, d404, d405, d406, d407, d408, d409, d410, d411"
                      "d501, d502, d503, d504, d505, d506, d507, d508, d509, d510, d511"
                            "VALUES (?, ?, ?, ?, ?, ?, "
                      "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
                      "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
                      "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
                      "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
                      "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,)");
        foreach (int temp, var) {
            query.addBindValue(temp);
        }
        query.exec();
    }

    // Qt Model-View 显示数据库
//    QSqlTableModel *model = new QSqlTableModel(this);
//    model->setTable("kjh");
//    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    model->select();
//    model->setHeaderData(0, Qt::Horizontal, tr("期号"));
//    model->setHeaderData(1, Qt::Horizontal, tr("一"));
//    model->setHeaderData(2, Qt::Horizontal, tr("二"));
//    model->setHeaderData(3, Qt::Horizontal, tr("三"));
//    model->setHeaderData(4, Qt::Horizontal, tr("四"));
//    model->setHeaderData(5, Qt::Horizontal, tr("五"));

//    ui->tableView_number->setModel(model);
//    ui->tableView_number->setColumnWidth(0,290);
//    ui->tableView_number->setColumnWidth(1,100);
//    ui->tableView_number->setColumnWidth(2,100);
//    ui->tableView_number->setColumnWidth(3,100);
//    ui->tableView_number->setColumnWidth(4,100);
//    ui->tableView_number->setColumnWidth(5,100);

}

/**
 * @brief MainWindow::on_btn_show_ana_clicked 显示分析号码的第2步的结果集
 */
void MainWindow::on_btn_show_ana_clicked()
{

}
