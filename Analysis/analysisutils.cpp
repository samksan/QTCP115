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
    // 分析号码循环,最后的号码的循环
    // 假设 num_base = 30, num_ana = 10 , 共有 100 期
    // 则循环最后10期, 90-99
    QMap<int,int> num_count;
    num_count[1] = 1;
    num_count[2] = 5;
    num_count[3] = 2;
    num_count[4] = 3;
    num_count[5] = 9;
    num_count[6] = 2;
    num_count[7] = 4;
    num_count[8] = 7;
    num_count[9] = 9;
    num_count[10] = 2;
    num_count[11] = 3;

//    qSort(num_count);

    for (int var = 1; var < 12; ++var) {
        qDebug() << num_count[var];
    }



    for (int num_now = num_total.length() - num_ana; num_now < num_total.length(); ++num_now) {
        int sn = num_total[num_now][0];
        int num1 = num_total[num_now].at(1);
        int num2 = num_total[num_now].at(2);
        int num3 = num_total[num_now].at(3);
        int num4 = num_total[num_now].at(4);
        int num5 = num_total[num_now].at(5);

        // 循环 num_now 之前的 num_base - 1 期号码
        for (int num_base_start = num_now - num_base; num_base_start < num_now - 1; ++num_base_start) {

            // 计算 num_now 第一个号码的跟随表
            if (num_total[num_base_start].contains(num1)) {

            }

        }




    }
}
