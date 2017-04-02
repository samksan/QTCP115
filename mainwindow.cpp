#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database/netnumbers.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTableView>

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include "Analysis/analysiscontrol.h"
#include "Analysis/analysisutils.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化数据库连接
    NetNumbers::initQSQLDatabase();
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
    model->setHeaderData(1, Qt::Horizontal, tr("号码1"));
    model->setHeaderData(2, Qt::Horizontal, tr("号码2"));
    model->setHeaderData(3, Qt::Horizontal, tr("号码3"));
    model->setHeaderData(4, Qt::Horizontal, tr("号码4"));
    model->setHeaderData(5, Qt::Horizontal, tr("号码5"));

    QTableView *table = new QTableView;
    table->setModel(model);
    table->setGeometry(160,160,1080,500);
    table->setColumnWidth(0,250);
    table->setColumnWidth(1,130);
    table->setColumnWidth(2,130);
    table->setColumnWidth(3,130);
    table->setColumnWidth(4,130);
    table->setColumnWidth(5,130);
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    table->show();
}

// 分析历史号码
void MainWindow::on_btnAnalysis_clicked()
{
    // 控制分析过程
    AnalysisControl ana;
    ana.start();
}

// 从网络获取开奖号码，并保存到数据库
void MainWindow::on_btn_update_number_clicked()
{
    NetNumbers::getHtml("http://ln11x5.icaile.com/?op=dcjb&num=100");
    QMessageBox::information(NULL,tr("号码更新提示"),tr("号码更新成功"),QMessageBox::Ok);

    // 号码 numbers_total => 100 * {期号, n1, n2, n3, n4, n5, n6}
    QVector<QVector<int>> numbers_total = NetNumbers::getNumbers();

    // 判断数据库数据是否为 100 期
    //    int numbers_length = numbers_total.length();
    if (numbers_total.length() != 100) {
        qDebug() << "期数总数错误";
        QMessageBox::critical(NULL,
                              tr("错误信息"),
                              tr("号码的期数不正确,可能是数据库数据错误"));
    }
}
