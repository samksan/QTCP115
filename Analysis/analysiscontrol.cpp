#include "analysiscontrol.h"
#include "analysisutils.h"
#include "database/netnumbers.h"
#include <QMessageBox>

AnalysisControl::AnalysisControl(QObject *parent) : QObject(parent)
{

}

/**
 * @brief AnalysisControl::start 控制号码分析流程
 * @param num_base 基础期数
 * @param num_ana 分析号码的期数
 * @param num_chart 显示图标的期数
 */
void AnalysisControl::start(const int num_base, const int num_ana, const int num_chart)
{
    // 号码 numbers_total => 100 * {期号, n1, n2, n3, n4, n5}
    QVector<QVector<int>> numbers_total = NetNumbers::getNumbers();

    // 第一步: 循环计算得出跟随表
    for (int loop = numbers_total.length() - num_ana; loop < numbers_total.length(); ++loop) {
        //
        qDebug() << loop;



    }

}
