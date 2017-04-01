#include "analysiscontrol.h"
#include "analysisutils.h"
#include "database/netnumbers.h"
#include <QMessageBox>

AnalysisControl::AnalysisControl(QObject *parent) : QObject(parent)
{

}

// 控制号码分析流程
void AnalysisControl::start()
{
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
