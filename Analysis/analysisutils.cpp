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

    // 存放 1-11 的出现次数
    QVector<int> vector_temp(11);

    // num_now 正在分析的号码行号
    for (int num_now = num_total.length() - num_ana; num_now < num_total.length(); ++num_now) {

        // 循环5个号码
        for (int var = 1; var <= 5; ++var) {

            // num 正在分析的号码
            int num = num_total[num_now].at(var);

            // 临时号码
            int int_temp1 = 0;
            int int_temp2 = 0;
            int int_temp3 = 0;
            int int_temp4 = 0;
            int int_temp5 = 0;

            // 循环 num_now 之前的 num_base - 1 期号码
            vector_temp.fill(0);
            for (int num_base_start = num_now - num_base; num_base_start < num_now; ++num_base_start) {

                // 计算 num_now 第一个号码的跟随表
                if (num_total[num_base_start].contains(num)) {

                    // 临时号码存储匹配项的下一期的5个号码
                    int_temp1 = num_total[num_base_start + 1][1];
                    int_temp2 = num_total[num_base_start + 1][2];
                    int_temp3 = num_total[num_base_start + 1][3];
                    int_temp4 = num_total[num_base_start + 1][4];
                    int_temp5 = num_total[num_base_start + 1][5];

                    // vector_temp存储号码的个数,0-10 表示 1-11
                    vector_temp[int_temp1 - 1] += 1;
                    vector_temp[int_temp2 - 1] += 1;
                    vector_temp[int_temp3 - 1] += 1;
                    vector_temp[int_temp4 - 1] += 1;
                    vector_temp[int_temp5 - 1] += 1;
                }
            }

            // 1-11 DESC 排序
            VectorDesc(vector_temp);

            // 把结果加入到数据集中
            for (int loops = 0; loops < vector_temp.length(); ++loops) {
                num_total[num_now] << vector_temp[loops];
            }

        }
    }
}

/**
 * @brief VectorDesc 修改传入的 QVector, 变成 1-11 的出现次数的多少排序DESC
 * @param vector 11个号码的出现次数
 */
void AnalysisUtils::VectorDesc(QVector<int> &vector)
{
    QVector<int> desc = vector;
    QVector<int> original = vector;
    int length = desc.length();
    QVector<int> result;
    qSort(desc);

    for (int var_desc = length - 1; var_desc >= 0; --var_desc) {
        for (int var_original = 0; var_original < length; ++var_original) {
            if (desc[var_desc] == original[var_original]) {
                result.append(var_original + 1);
                original[var_original] = -1;
                break;
            }
        }
    }

    vector = result;
}

















