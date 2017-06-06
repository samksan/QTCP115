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

#include <QtCharts>

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

    ui->btn_data_refresh->click();

    // 控制分析过程
    AnalysisControl ana;
    ana.start(num_base, num_ana, num_chart);
}

/**
 * @brief MainWindow::on_btn_update_number_clicked 按钮函数（更新号码）的函数
 */
void MainWindow::on_btn_update_number_clicked()
{
    // 从网络获取开奖号码，并保存到数据库
    NetNumbers::getHtmlFrom360();

    // 号码 numbers_total => 100 * {期号, n1, n2, n3, n4, n5, n6}
    DataAll::numbers_all = NetNumbers::getNumbers();

    // 判断数据库数据是否正确
    foreach (QVector<int> var, DataAll::numbers_all) {
        if (var[1] < 0 || var[1] > 11 || var[2] < 0 || var[2] > 11 || var[3] < 0 || var[3] > 11 || var[4] < 0 || var[4] > 11 | var[5] < 0 || var[5] > 11) {
            QMessageBox::critical(NULL,
                                  tr("错误信息"),
                                  tr("获取开奖号码时出错，请确认网络可用，并重新获取数据"));
            return;
        }
    }

    QStringList list;
    int length = DataAll::numbers_all.length();
    list << "更新号码详细信息：";
    list << "总期数： " + QString::number(length);
    list << "开始期数: " + QString::number(DataAll::numbers_all[0][0]);
    list << "结束期数: " + QString::number(DataAll::numbers_all[length - 1][0]);

    QString str = list.join("\n");
    // 更新成功的提示信息
    QMessageBox::information(NULL, tr("号码更新提示"), str, QMessageBox::Ok);
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
        return;
    }

}


void MainWindow::on_pushButton_zdd1_clicked()
{
    if(ui->check_zdd01->isChecked()){
        ui->check_zdd01->setChecked(false);
        ui->check_zdd02->setChecked(false);
        ui->check_zdd03->setChecked(false);
        ui->check_zdd04->setChecked(false);
        ui->check_zdd05->setChecked(false);
        ui->check_zdd06->setChecked(false);
        ui->check_zdd07->setChecked(false);
    }else{
        ui->check_zdd01->setChecked(true);
        ui->check_zdd02->setChecked(true);
        ui->check_zdd03->setChecked(true);
        ui->check_zdd04->setChecked(true);
        ui->check_zdd05->setChecked(true);
        ui->check_zdd06->setChecked(true);
        ui->check_zdd07->setChecked(true);
    }
}

void MainWindow::on_pushButton_zdd2_clicked()
{
    if(ui->check_zdd08->isChecked()){
        ui->check_zdd08->setChecked(false);
        ui->check_zdd09->setChecked(false);
        ui->check_zdd10->setChecked(false);
        ui->check_zdd11->setChecked(false);
        ui->check_zdd12->setChecked(false);
        ui->check_zdd13->setChecked(false);
        ui->check_zdd14->setChecked(false);
    }else{
        ui->check_zdd08->setChecked(true);
        ui->check_zdd09->setChecked(true);
        ui->check_zdd10->setChecked(true);
        ui->check_zdd11->setChecked(true);
        ui->check_zdd12->setChecked(true);
        ui->check_zdd13->setChecked(true);
        ui->check_zdd14->setChecked(true);
    }
}

void MainWindow::on_pushButton_zdd3_clicked()
{
    if(ui->check_zdd15->isChecked()){
        ui->check_zdd15->setChecked(false);
        ui->check_zdd16->setChecked(false);
        ui->check_zdd17->setChecked(false);
        ui->check_zdd18->setChecked(false);
        ui->check_zdd19->setChecked(false);
        ui->check_zdd20->setChecked(false);
        ui->check_zdd21->setChecked(false);
    }else{
        ui->check_zdd15->setChecked(true);
        ui->check_zdd16->setChecked(true);
        ui->check_zdd17->setChecked(true);
        ui->check_zdd18->setChecked(true);
        ui->check_zdd19->setChecked(true);
        ui->check_zdd20->setChecked(true);
        ui->check_zdd21->setChecked(true);
    }
}

void MainWindow::on_pushButton_bdd1_clicked()
{
    if(ui->check_bdd01->isChecked()){
        ui->check_bdd01->setChecked(false);
        ui->check_bdd02->setChecked(false);
        ui->check_bdd03->setChecked(false);
        ui->check_bdd04->setChecked(false);
        ui->check_bdd05->setChecked(false);
        ui->check_bdd06->setChecked(false);
        ui->check_bdd07->setChecked(false);
    }else{
        ui->check_bdd01->setChecked(true);
        ui->check_bdd02->setChecked(true);
        ui->check_bdd03->setChecked(true);
        ui->check_bdd04->setChecked(true);
        ui->check_bdd05->setChecked(true);
        ui->check_bdd06->setChecked(true);
        ui->check_bdd07->setChecked(true);
    }
}

void MainWindow::on_pushButton_bdd2_clicked()
{
    if(ui->check_bdd08->isChecked()){
        ui->check_bdd08->setChecked(false);
        ui->check_bdd09->setChecked(false);
        ui->check_bdd10->setChecked(false);
        ui->check_bdd11->setChecked(false);
        ui->check_bdd12->setChecked(false);
        ui->check_bdd13->setChecked(false);
        ui->check_bdd14->setChecked(false);
    }else{
        ui->check_bdd08->setChecked(true);
        ui->check_bdd09->setChecked(true);
        ui->check_bdd10->setChecked(true);
        ui->check_bdd11->setChecked(true);
        ui->check_bdd12->setChecked(true);
        ui->check_bdd13->setChecked(true);
        ui->check_bdd14->setChecked(true);
    }
}

void MainWindow::on_pushButton_bdd3_clicked()
{
    if(ui->check_bdd15->isChecked()){
        ui->check_bdd15->setChecked(false);
        ui->check_bdd16->setChecked(false);
        ui->check_bdd17->setChecked(false);
        ui->check_bdd18->setChecked(false);
        ui->check_bdd19->setChecked(false);
        ui->check_bdd20->setChecked(false);
        ui->check_bdd21->setChecked(false);
    }else{
        ui->check_bdd15->setChecked(true);
        ui->check_bdd16->setChecked(true);
        ui->check_bdd17->setChecked(true);
        ui->check_bdd18->setChecked(true);
        ui->check_bdd19->setChecked(true);
        ui->check_bdd20->setChecked(true);
        ui->check_bdd21->setChecked(true);
    }
}

void MainWindow::on_pushButton_zdz1_clicked()
{
    if(ui->check_zdz01->isChecked()){
        ui->check_zdz01->setChecked(false);
        ui->check_zdz02->setChecked(false);
        ui->check_zdz03->setChecked(false);
        ui->check_zdz04->setChecked(false);
        ui->check_zdz05->setChecked(false);
        ui->check_zdz06->setChecked(false);
        ui->check_zdz07->setChecked(false);
    }else{
        ui->check_zdz01->setChecked(true);
        ui->check_zdz02->setChecked(true);
        ui->check_zdz03->setChecked(true);
        ui->check_zdz04->setChecked(true);
        ui->check_zdz05->setChecked(true);
        ui->check_zdz06->setChecked(true);
        ui->check_zdz07->setChecked(true);
    }
}

void MainWindow::on_pushButton_zdz2_clicked()
{
    if(ui->check_zdz08->isChecked()){
        ui->check_zdz08->setChecked(false);
        ui->check_zdz09->setChecked(false);
        ui->check_zdz10->setChecked(false);
        ui->check_zdz11->setChecked(false);
        ui->check_zdz12->setChecked(false);
        ui->check_zdz13->setChecked(false);
        ui->check_zdz14->setChecked(false);
    }else{
        ui->check_zdz08->setChecked(true);
        ui->check_zdz09->setChecked(true);
        ui->check_zdz10->setChecked(true);
        ui->check_zdz11->setChecked(true);
        ui->check_zdz12->setChecked(true);
        ui->check_zdz13->setChecked(true);
        ui->check_zdz14->setChecked(true);
    }
}

void MainWindow::on_pushButton_zdz3_clicked()
{
    if(ui->check_zdz15->isChecked()){
        ui->check_zdz15->setChecked(false);
        ui->check_zdz16->setChecked(false);
        ui->check_zdz17->setChecked(false);
        ui->check_zdz18->setChecked(false);
        ui->check_zdz19->setChecked(false);
        ui->check_zdz20->setChecked(false);
        ui->check_zdz21->setChecked(false);
    }else{
        ui->check_zdz15->setChecked(true);
        ui->check_zdz16->setChecked(true);
        ui->check_zdz17->setChecked(true);
        ui->check_zdz18->setChecked(true);
        ui->check_zdz19->setChecked(true);
        ui->check_zdz20->setChecked(true);
        ui->check_zdz21->setChecked(true);
    }
}

void MainWindow::on_pushButton_bdz1_clicked()
{
    if(ui->check_bdz01->isChecked()){
        ui->check_bdz01->setChecked(false);
        ui->check_bdz02->setChecked(false);
        ui->check_bdz03->setChecked(false);
        ui->check_bdz04->setChecked(false);
        ui->check_bdz05->setChecked(false);
        ui->check_bdz06->setChecked(false);
        ui->check_bdz07->setChecked(false);
    }else{
        ui->check_bdz01->setChecked(true);
        ui->check_bdz02->setChecked(true);
        ui->check_bdz03->setChecked(true);
        ui->check_bdz04->setChecked(true);
        ui->check_bdz05->setChecked(true);
        ui->check_bdz06->setChecked(true);
        ui->check_bdz07->setChecked(true);
    }
}

void MainWindow::on_pushButton_bdz2_clicked()
{
    if(ui->check_bdz08->isChecked()){
        ui->check_bdz08->setChecked(false);
        ui->check_bdz09->setChecked(false);
        ui->check_bdz10->setChecked(false);
        ui->check_bdz11->setChecked(false);
        ui->check_bdz12->setChecked(false);
        ui->check_bdz13->setChecked(false);
        ui->check_bdz14->setChecked(false);
    }else{
        ui->check_bdz08->setChecked(true);
        ui->check_bdz09->setChecked(true);
        ui->check_bdz10->setChecked(true);
        ui->check_bdz11->setChecked(true);
        ui->check_bdz12->setChecked(true);
        ui->check_bdz13->setChecked(true);
        ui->check_bdz14->setChecked(true);
    }
}

void MainWindow::on_pushButton_bdz3_clicked()
{
    if(ui->check_bdz15->isChecked()){
        ui->check_bdz15->setChecked(false);
        ui->check_bdz16->setChecked(false);
        ui->check_bdz17->setChecked(false);
        ui->check_bdz18->setChecked(false);
        ui->check_bdz19->setChecked(false);
        ui->check_bdz20->setChecked(false);
        ui->check_bdz21->setChecked(false);
    }else{
        ui->check_bdz15->setChecked(true);
        ui->check_bdz16->setChecked(true);
        ui->check_bdz17->setChecked(true);
        ui->check_bdz18->setChecked(true);
        ui->check_bdz19->setChecked(true);
        ui->check_bdz20->setChecked(true);
        ui->check_bdz21->setChecked(true);
    }
}

/**
 * @brief MainWindow::on_pushButton_filter_clicked 遗传过滤按钮事件
 */
void MainWindow::on_pushButton_filter_clicked()
{
    QVector<int> zdd, zdz, bdd, bdz;

    zdd.clear();
    if(ui->check_zdd01->isChecked())
        zdd << 1;
    if(ui->check_zdd02->isChecked())
        zdd << 2;
    if(ui->check_zdd03->isChecked())
        zdd << 3;
    if(ui->check_zdd04->isChecked())
        zdd << 4;
    if(ui->check_zdd05->isChecked())
        zdd << 5;
    if(ui->check_zdd06->isChecked())
        zdd << 6;
    if(ui->check_zdd07->isChecked())
        zdd << 7;
    if(ui->check_zdd08->isChecked())
        zdd << 8;
    if(ui->check_zdd09->isChecked())
        zdd << 9;
    if(ui->check_zdd10->isChecked())
        zdd << 10;
    if(ui->check_zdd11->isChecked())
        zdd << 11;
    if(ui->check_zdd12->isChecked())
        zdd << 12;
    if(ui->check_zdd13->isChecked())
        zdd << 13;
    if(ui->check_zdd14->isChecked())
        zdd << 14;
    if(ui->check_zdd15->isChecked())
        zdd << 15;
    if(ui->check_zdd16->isChecked())
        zdd << 16;
    if(ui->check_zdd17->isChecked())
        zdd << 17;
    if(ui->check_zdd18->isChecked())
        zdd << 18;
    if(ui->check_zdd19->isChecked())
        zdd << 19;
    if(ui->check_zdd20->isChecked())
        zdd << 20;
    if(ui->check_zdd21->isChecked())
        zdd << 21;

    zdz.clear();
    if(ui->check_zdz01->isChecked())
        zdz << 1;
    if(ui->check_zdz02->isChecked())
        zdz << 2;
    if(ui->check_zdz03->isChecked())
        zdz << 3;
    if(ui->check_zdz04->isChecked())
        zdz << 4;
    if(ui->check_zdz05->isChecked())
        zdz << 5;
    if(ui->check_zdz06->isChecked())
        zdz << 6;
    if(ui->check_zdz07->isChecked())
        zdz << 7;
    if(ui->check_zdz08->isChecked())
        zdz << 8;
    if(ui->check_zdz09->isChecked())
        zdz << 9;
    if(ui->check_zdz10->isChecked())
        zdz << 10;
    if(ui->check_zdz11->isChecked())
        zdz << 11;
    if(ui->check_zdz12->isChecked())
        zdz << 12;
    if(ui->check_zdz13->isChecked())
        zdz << 13;
    if(ui->check_zdz14->isChecked())
        zdz << 14;
    if(ui->check_zdz15->isChecked())
        zdz << 15;
    if(ui->check_zdz16->isChecked())
        zdz << 16;
    if(ui->check_zdz17->isChecked())
        zdz << 17;
    if(ui->check_zdz18->isChecked())
        zdz << 18;
    if(ui->check_zdz19->isChecked())
        zdz << 19;
    if(ui->check_zdz20->isChecked())
        zdz << 20;
    if(ui->check_zdz21->isChecked())
        zdz << 21;

    bdd.clear();
    if(ui->check_bdd01->isChecked())
        bdd << 1;
    if(ui->check_bdd02->isChecked())
        bdd << 2;
    if(ui->check_bdd03->isChecked())
        bdd << 3;
    if(ui->check_bdd04->isChecked())
        bdd << 4;
    if(ui->check_bdd05->isChecked())
        bdd << 5;
    if(ui->check_bdd06->isChecked())
        bdd << 6;
    if(ui->check_bdd07->isChecked())
        bdd << 7;
    if(ui->check_bdd08->isChecked())
        bdd << 8;
    if(ui->check_bdd09->isChecked())
        bdd << 9;
    if(ui->check_bdd10->isChecked())
        bdd << 10;
    if(ui->check_bdd11->isChecked())
        bdd << 11;
    if(ui->check_bdd12->isChecked())
        bdd << 12;
    if(ui->check_bdd13->isChecked())
        bdd << 13;
    if(ui->check_bdd14->isChecked())
        bdd << 14;
    if(ui->check_bdd15->isChecked())
        bdd << 15;
    if(ui->check_bdd16->isChecked())
        bdd << 16;
    if(ui->check_bdd17->isChecked())
        bdd << 17;
    if(ui->check_bdd18->isChecked())
        bdd << 18;
    if(ui->check_bdd19->isChecked())
        bdd << 19;
    if(ui->check_bdd20->isChecked())
        bdd << 20;
    if(ui->check_bdd21->isChecked())
        bdd << 21;

    bdz.clear();
    if(ui->check_bdz01->isChecked())
        bdz << 1;
    if(ui->check_bdz02->isChecked())
        bdz << 2;
    if(ui->check_bdz03->isChecked())
        bdz << 3;
    if(ui->check_bdz04->isChecked())
        bdz << 4;
    if(ui->check_bdz05->isChecked())
        bdz << 5;
    if(ui->check_bdz06->isChecked())
        bdz << 6;
    if(ui->check_bdz07->isChecked())
        bdz << 7;
    if(ui->check_bdz08->isChecked())
        bdz << 8;
    if(ui->check_bdz09->isChecked())
        bdz << 9;
    if(ui->check_bdz10->isChecked())
        bdz << 10;
    if(ui->check_bdz11->isChecked())
        bdz << 11;
    if(ui->check_bdz12->isChecked())
        bdz << 12;
    if(ui->check_bdz13->isChecked())
        bdz << 13;
    if(ui->check_bdz14->isChecked())
        bdz << 14;
    if(ui->check_bdz15->isChecked())
        bdz << 15;
    if(ui->check_bdz16->isChecked())
        bdz << 16;
    if(ui->check_bdz17->isChecked())
        bdz << 17;
    if(ui->check_bdz18->isChecked())
        bdz << 18;
    if(ui->check_bdz19->isChecked())
        bdz << 19;
    if(ui->check_bdz20->isChecked())
        bdz << 20;
    if(ui->check_bdz21->isChecked())
        bdz << 21;

    AnalysisUtils::s4_filter(zdd, zdz, bdd, bdz);
}



void MainWindow::on_chart_zdd_1_clicked()
{
    this->chart_view(6);
}

void MainWindow::on_chart_zdd_2_clicked()
{
    this->chart_view(7);
}

void MainWindow::on_chart_zdd_3_clicked()
{
    this->chart_view(8);
}

void MainWindow::on_chart_zdd_4_clicked()
{
    this->chart_view(9);
}

void MainWindow::on_chart_zdd_5_clicked()
{
    this->chart_view(10);
}

void MainWindow::on_chart_bdd_1_clicked()
{
    this->chart_view(11);
}

void MainWindow::on_chart_bdd_2_clicked()
{
    this->chart_view(12);
}

void MainWindow::on_chart_bdd_3_clicked()
{
    this->chart_view(13);
}

void MainWindow::on_chart_bdd_4_clicked()
{
    this->chart_view(14);
}

void MainWindow::on_chart_bdd_5_clicked()
{
    this->chart_view(15);
}

void MainWindow::on_chart_zdz_1_clicked()
{
    this->chart_view(16);
}

void MainWindow::on_chart_zdz_2_clicked()
{
    this->chart_view(17);
}

void MainWindow::on_chart_zdz_3_clicked()
{
    this->chart_view(18);
}

void MainWindow::on_chart_zdz_4_clicked()
{
    this->chart_view(19);
}

void MainWindow::on_chart_zdz_5_clicked()
{
    this->chart_view(20);
}

void MainWindow::on_chart_bdz_1_clicked()
{
    this->chart_view(21);
}

void MainWindow::on_chart_bdz_2_clicked()
{
    this->chart_view(22);
}

void MainWindow::on_chart_bdz_3_clicked()
{
    this->chart_view(23);
}

void MainWindow::on_chart_bdz_4_clicked()
{
    this->chart_view(24);
}

void MainWindow::on_chart_bdz_5_clicked()
{
    this->chart_view(25);
}

/**
 * @brief MainWindow::chart_view 图表显示函数
 * @param position 数据在 vector 中的位置
 */
void MainWindow::chart_view(int position)
{
    if(DataAll::numbers_chart.isEmpty()){
        QMessageBox::information(NULL, tr("没有数据"), tr("必须分析数据之后才可以查看结果"), QMessageBox::Ok);
        return;
    }
    QLineSeries *series = new QLineSeries();

    for (int var = 0; var < DataAll::numbers_chart.length(); ++var) {
        series->append(var,DataAll::numbers_chart[var][position]);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("分析结果走势图");

    series->setPointLabelsVisible(true);
    series->setPointsVisible(true);
    series->setPointLabelsFormat("@yPoint");
    series->setPen(QPen(Qt::darkGreen,1,Qt::SolidLine));
    series->setPointLabelsClipping(false);
    series->setPointLabelsFont(QFont("menlo",16,QFont::Bold));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    if(!ui->chart_layout->isEmpty()){
        ui->chart_layout->removeItem(ui->chart_layout->itemAt(0));
        ui->chart_layout->addWidget(chartView);
    }else{
        ui->chart_layout->addWidget(chartView);
    }
}
