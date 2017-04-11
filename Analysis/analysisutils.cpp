#include "analysisutils.h"
#include <QVector>
#include <QDebug>

AnalysisUtils::AnalysisUtils(QObject *parent) : QObject(parent)
{

}

/**
 * @brief AnalysisUtils::s1_follow void 第一步: 循环计算得出跟随表
 * @param num_total QVector<Qvector<int> > 全部数据集合
 * @param num_base int 基础期数
 * @param num_ana int 分析期数
 */
void AnalysisUtils::s1_follow(QVector<QVector<int>> &num_total, const int num_base, const int num_ana)
{
    qDebug() << "before";
    qDebug() << num_total[0][0];
    num_total[0][0] = 666;

    qDebug() << "after";
    qDebug() << num_total[0][0];

}
