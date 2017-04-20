#include "NetNumbers.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QDebug>

/**
 * @brief NetNumbers::getNumbers 从数据库中获取开奖号码
 * @return QList<QList<int>> 返回开奖号码
 */
QVector<QVector<int>> NetNumbers::getNumbers()
{
    // 获取数据库连接
    QSqlDatabase db = QSqlDatabase::database();

    // 获取数据库内容，把内容放进 QList 容器，并返回
    QSqlQuery query;
    query.exec("SELECT * FROM kjh");

    QVector<QVector<int>> list;
    while(query.next())
    {
       QVector<int> temp;
       temp.append(query.value(0).toInt());
       temp.append(query.value(1).toInt());
       temp.append(query.value(2).toInt());
       temp.append(query.value(3).toInt());
       temp.append(query.value(4).toInt());
       temp.append(query.value(5).toInt());
       list.append(temp);
    }

    db.close();
    return list;
}

/**
 * @brief NetNumbers::toDB 把从网络获取的二维数组（开奖号码）保存到数据库
 * @param number 从网络得到的开奖号码
 */
void NetNumbers::toDB(int number[100][6])
{
    // 获取数据库连接
    QSqlDatabase db = QSqlDatabase::database();

    // 格式化数据表，保存开奖号
    QSqlQuery query;
    query.exec("delete from kjh");
    query.prepare("INSERT INTO kjh VALUES(?,?,?,?,?,?)");
    for (int var = 0; var < 100; ++var) {
        query.bindValue(0,number[var][0]);
        query.bindValue(1,number[var][1]);
        query.bindValue(2,number[var][2]);
        query.bindValue(3,number[var][3]);
        query.bindValue(4,number[var][4]);
        query.bindValue(5,number[var][5]);
        query.exec();
    }

    query.exec("select * from kjh");

    int total = 0;
    while (query.next()) {
        total++;
    }
    if(total == 100)
        qDebug() << "数据更新成功" << endl;
    else
        qDebug() << "数据更新失败" << endl;

    db.close();
}

/**
 * @brief NetNumbers::initQSQLDatabase 初始化数据库连接，在任意位置都可以获取到数据库连接实例
 */
void NetNumbers::initQSQLDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("kjhdb.db");
    db.open();

    QSqlQuery query;
    query.exec("create table if not exists kjh(sn int primarykey,n1 int,n2 int,n3 int,n4 int,n5 int)");
    query.exec("create table if not exists ana(sn int primarykey, n1 int, n2 int, n3 int, n4 int, n5 int,"
               "d101 int,d102 int,d103 int,d104 int,d105 int,d106 int,d107 int,d108 int,d109 int,d110 int,d111 int,"
               "d201 int,d202 int,d203 int,d204 int,d205 int,d206 int,d207 int,d208 int,d209 int,d210 int,d211 int,"
               "d301 int,d302 int,d303 int,d304 int,d305 int,d306 int,d307 int,d308 int,d309 int,d310 int,d311 int,"
               "d401 int,d402 int,d403 int,d404 int,d405 int,d406 int,d407 int,d408 int,d409 int,d410 int,d411 int,"
               "d501 int,d502 int,d503 int,d504 int,d505 int,d506 int,d507 int,d508 int,d509 int,d510 int,d511 int)");

}

/**
 * @brief NetNumbers::getHtml 通过网站过滤得到开奖号码
 * @param url 获取开奖号码的网址
 */
void NetNumbers::getHtml(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QByteArray responseData;
    QEventLoop eventLoop;
    connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();       //block until finish
    responseData = reply->readAll();
    strToDB(responseData);
}

/**
 * @brief NetNumbers::strToDB 处理从网络获取到的字符串，调用函数生成开奖号保存到数据库
 * @param str 从网络获取到的字符串
 */
void NetNumbers::strToDB(QString str)
{
    QStringList list;
    QString temp = "<td class=\"chart-bg-qh\">";

    // 分隔成101个字符串（1 - 100）包含开奖号码，0是网站的信息头
    list = str.split(temp);
    list.removeFirst();

    QString sn,s1,s2,s3,s4,s5;
    int result[100][6];

    for (int var = 0; var < list.size(); ++var) {

        // 临时 QStringList
        QStringList tempList;

        // 分割字符串所需的字符串
        QString splitString = "dqhm";
        QString splitString2 = "kjhmo";

        // 当前期号的整体字符串
        QString stringTemp = list[var];

        tempList = stringTemp.split(splitString);

        sn = tempList[0].mid(0,8);
        s2 = tempList[1].mid(2,2);
        s3 = tempList[2].mid(2,2);
        s4 = tempList[3].mid(2,2);
        s5 = tempList[4].mid(2,2);

        tempList.clear();
        tempList = stringTemp.split(splitString2);
        s1 = tempList[1].mid(2,2);

        result[var][0] = sn.toInt();
        result[var][1] = s1.toInt();
        result[var][2] = s2.toInt();
        result[var][3] = s3.toInt();
        result[var][4] = s4.toInt();
        result[var][5] = s5.toInt();
    }
    NetNumbers::toDB(result);

}




