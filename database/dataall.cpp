#include "dataall.h"
#include "netnumbers.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

DataAll::DataAll(QObject *parent) : QObject(parent)
{

}

void DataAll::InitMap()
{
    DataAll::dic_desc_num[5] = 1;
    DataAll::dic_desc_num[14] = 2;
    DataAll::dic_desc_num[23] = 3;
    DataAll::dic_desc_num[32] = 4;
    DataAll::dic_desc_num[41] = 5;
    DataAll::dic_desc_num[50] = 6;
    DataAll::dic_desc_num[104] = 7;
    DataAll::dic_desc_num[113] = 8;
    DataAll::dic_desc_num[122] = 9;
    DataAll::dic_desc_num[131] = 10;
    DataAll::dic_desc_num[140] = 11;
    DataAll::dic_desc_num[203] = 12;
    DataAll::dic_desc_num[212] = 13;
    DataAll::dic_desc_num[221] = 14;
    DataAll::dic_desc_num[230] = 15;
    DataAll::dic_desc_num[302] = 16;
    DataAll::dic_desc_num[311] = 17;
    DataAll::dic_desc_num[320] = 18;
    DataAll::dic_desc_num[401] = 19;
    DataAll::dic_desc_num[410] = 20;
    DataAll::dic_desc_num[500] = 21;

    DataAll::dic_num_desc[1] = 5;
    DataAll::dic_num_desc[2] = 14;
    DataAll::dic_num_desc[3] = 23;
    DataAll::dic_num_desc[4] = 32;
    DataAll::dic_num_desc[5] = 41;
    DataAll::dic_num_desc[6] = 50;
    DataAll::dic_num_desc[7] = 104;
    DataAll::dic_num_desc[8] = 113;
    DataAll::dic_num_desc[9] = 122;
    DataAll::dic_num_desc[10] = 131;
    DataAll::dic_num_desc[11] = 140;
    DataAll::dic_num_desc[12] = 203;
    DataAll::dic_num_desc[13] = 212;
    DataAll::dic_num_desc[14] = 221;
    DataAll::dic_num_desc[15] = 230;
    DataAll::dic_num_desc[16] = 302;
    DataAll::dic_num_desc[17] = 311;
    DataAll::dic_num_desc[18] = 320;
    DataAll::dic_num_desc[19] = 401;
    DataAll::dic_num_desc[20] = 410;
    DataAll::dic_num_desc[21] = 500;
}

void DataAll::ana_to_database()
{
    // DataAll::numbers_ana 写入数据库
    // 获取数据库连接，测试连接是否成功
    QSqlDatabase db = QSqlDatabase::database();
    bool ok = db.open();
    if(!ok){
        QMessageBox::information(NULL, "数据库连接失败", "数据库连接失败!!!", QMessageBox::Ok);
    }

    QSqlQuery query;
    query.exec("DELETE FROM ana");
    foreach (QVector<int> var, DataAll::numbers_ana) {
        query.prepare("insert into ana (sn, n1, n2, n3, n4, n5,"
                      "d101,d102,d103,d104,d105,d106,d107,d108,d109,d110,d111,"
                      "d201,d202,d203,d204,d205,d206,d207,d208,d209,d210,d211,"
                      "d301,d302,d303,d304,d305,d306,d307,d308,d309,d310,d311,"
                      "d401,d402,d403,d404,d405,d406,d407,d408,d409,d410,d411,"
                      "d501,d502,d503,d504,d505,d506,d507,d508,d509,d510,d511) "
                      " VALUES (?, ?, ?, ?, ?, ?, "
                      "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
                      "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
                      "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
                      "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
                      "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        foreach (int temp, var) {
            query.addBindValue(temp);
        }
        query.exec();
    }
}

void DataAll::zdbd_to_database()
{
    // DataAll::numbers_zdbd 写入数据库
    // 获取数据库连接，测试连接是否成功
    QSqlDatabase db = QSqlDatabase::database();
    bool ok = db.open();
    if(!ok){
        QMessageBox::information(NULL, "数据库连接失败", "数据库连接失败!!!", QMessageBox::Ok);
    }

    QSqlQuery query;
    query.exec("DELETE FROM zdbd");
    foreach (QVector<int> var, DataAll::numbers_zdbd) {
        query.prepare("insert into zdbd (sn, n1, n2, n3, n4, n5, nn1, nn2, nn3, nn4, nn5, "
                      "zd1, zd2, zd3, zd4, zd5, bd1, bd2, bd3, bd4, bd5)"
                      " VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
                      " ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        foreach (int temp, var) {
            query.addBindValue(temp);
        }
        query.exec();
    }
}

void DataAll::chart_to_database()
{
    // DataAll::numbers_zdbd 写入数据库
    // 获取数据库连接，测试连接是否成功
    QSqlDatabase db = QSqlDatabase::database();
    bool ok = db.open();
    if(!ok){
        QMessageBox::information(NULL, "数据库连接失败", "数据库连接失败!!!", QMessageBox::Ok);
    }

    QSqlQuery query;
    query.exec("DELETE FROM chart");
    foreach (QVector<int> var, DataAll::numbers_chart) {
        query.prepare("insert into chart (sn, n1, n2, n3, n4, n5, "
                      "zdd1, zdd2, zdd3, zdd4, zdd5, bdd1, bdd2, bdd3, bdd4, bdd5, "
                      "zdz1, zdz2, zdz3, zdz4, zdz5, bdz1, bdz2, bdz3, bdz4, bdz5) "
                      "VALUES (?, ?, ?, ?, ?, ?, "
                      "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
                      "?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        foreach (int temp, var) {
            query.addBindValue(temp);
        }
        query.exec();
    }
}

QVector<QVector<int>> DataAll::numbers_all;
QVector<QVector<int>> DataAll::numbers_ana;
QVector<QVector<int>> DataAll::numbers_zdbd;
QVector<QVector<int>> DataAll::numbers_chart;
QMap<int,int> DataAll::dic_desc_num;
QMap<int,int> DataAll::dic_num_desc;
