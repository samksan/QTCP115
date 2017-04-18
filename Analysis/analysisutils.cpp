#include "analysisutils.h"
#include <QVector>
#include <QDebug>
#include "database/dataall.h"

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
//            num_total[num_now] << vector_temp;

        }
    }
}

/**
 * @brief AnalysisUtils::s2_zdbd 第二步: 根据开奖号码计算得到 zdbd 主动和别动,添加到开奖号码后面
 * @param num_total 所有分析数据的集合
 * @param num_ana 分析的期数
 */
void AnalysisUtils::s2_zdbd(QVector<QVector<int> > &num_total, const int num_ana)
{
    // 跟随表分区
    // num_total 目前的格式:
    // num_ana之前(原始数据): sn(期号),n1(号1),n2(号2),n3(号3),n4(号4),n5(号5)
    // num_ana之后(跟随表   ): 多出了55个数字, desc11(11个号码的出现次数降序排序) * 5 = 55 个数字

    // 循环分析号码(包含跟随表的数据), 不包含最后一期,因为最后一期没有下一期的结果
    for (int num_now = num_total.length() - num_ana; num_now < num_total.length() - 1; ++num_now) {

        // 分析的号码的下一期号码
        int num_next1 = num_total[num_now + 1][1];
        int num_next2 = num_total[num_now + 1][2];
        int num_next3 = num_total[num_now + 1][3];
        int num_next4 = num_total[num_now + 1][4];
        int num_next5 = num_total[num_now + 1][5];

        // zd abcde
        QVector<int> desc_a = num_total[num_now].mid(6,11);
        QVector<int> desc_b = num_total[num_now].mid(17,11);
        QVector<int> desc_c = num_total[num_now].mid(28,11);
        QVector<int> desc_d = num_total[num_now].mid(39,11);
        QVector<int> desc_e = num_total[num_now].mid(50,11);

        // 主动计算
        int trans_int = ZD_ANA(desc_a, num_next1, num_next2, num_next3, num_next4, num_next1);
        num_total[num_now] << trans_int;
        trans_int = ZD_ANA(desc_b, num_next1, num_next2, num_next3, num_next4, num_next1);
        num_total[num_now] << trans_int;
        trans_int = ZD_ANA(desc_c, num_next1, num_next2, num_next3, num_next4, num_next1);
        num_total[num_now] << trans_int;
        trans_int = ZD_ANA(desc_d, num_next1, num_next2, num_next3, num_next4, num_next1);
        num_total[num_now] << trans_int;
        trans_int = ZD_ANA(desc_e, num_next1, num_next2, num_next3, num_next4, num_next1);
        num_total[num_now] << trans_int;

        // 被动计算
        trans_int = BD_ANA(desc_a, desc_b, desc_c, desc_d, desc_e, num_next1);
        num_total[num_now] << trans_int;
        trans_int = BD_ANA(desc_a, desc_b, desc_c, desc_d, desc_e, num_next2);
        num_total[num_now] << trans_int;
        trans_int = BD_ANA(desc_a, desc_b, desc_c, desc_d, desc_e, num_next3);
        num_total[num_now] << trans_int;
        trans_int = BD_ANA(desc_a, desc_b, desc_c, desc_d, desc_e, num_next4);
        num_total[num_now] << trans_int;
        trans_int = BD_ANA(desc_a, desc_b, desc_c, desc_d, desc_e, num_next5);
        num_total[num_now] << trans_int;

    }
}

/**
 * @brief AnalysisUtils::s3_zdbd_ana 第三步: 根据本期号码、开奖号码、主动、被动和 num_chart 计算得出规律(主动单,主动整,被动单,被动整)
 * @param num_total 所有分析数据的集合
 * @param num_ana 分析的期数
 * @param num_chart 显示的图表期数
 */
void AnalysisUtils::s3_zdbd_ana(QVector<QVector<int> > &num_total, const int num_ana, const int num_chart)
{
    // num_total 目前的格式:
    // 最后的 num_ana 期之前
    // 原始数据: sn(期号),n1(号1),n2(号2),n3(号3),n4(号4),n5(号5)  pointer(0-5)
    // 最后的 num_ana 期
    // 跟随表: 多出了55个数字, desc11(11个号码的出现次数降序排序) * 5 = 55 个数字   point(6-60)
    // 主动表: 多出了5个数字 pointer(61-65)
    // 被动表: 多出了5个数字 pointer(66-70)

    // 循环分析号码(包含跟随表的数据), 不包含最后一期,因为最后一期没有下一期的结果
    QVector<int> collection_zdbd;

    // 临时存储个数的 QVector 1-21
    QVector<int> temp(21);
    for (int num_now = num_total.length() - num_chart; num_now < num_total.length() - 1; ++num_now) {
        collection_zdbd.clear();
        temp.fill(0);
        // 主动单

        // 循环 1-5 个号码
        for (int loop5 = 1; loop5 <= 5; ++loop5) {
            int num = num_total[num_now][loop5];
            for (int loop_ana = num_total.length() - num_ana; loop_ana < num_now; ++loop_ana) {
                if (num_total[loop_ana].mid(1,5).contains(num)) {
                    temp[num_total[loop_ana][61] - 1] += 1;
                    temp[num_total[loop_ana][62] - 1] += 1;
                    temp[num_total[loop_ana][63] - 1] += 1;
                    temp[num_total[loop_ana][64] - 1] += 1;
                    temp[num_total[loop_ana][65] - 1] += 1;
                    qDebug() << collection_zdbd;
                }
            }

            // temp 排序
            VectorDesc(temp);
            int position = temp.indexOf(num_total[num_now][60 + loop5]) + 1;
            temp.fill(0);
            num_total[num_now] << position;
        }

        // 被动单
        // 循环 1-5 个号码
        for (int loop5 = 1; loop5 <= 5; ++loop5) {
            int num = num_total[num_now + 1][loop5];
            for (int loop_ana = num_total.length() - num_ana + 1; loop_ana < num_now - 1; ++loop_ana) {
                if (num_total[loop_ana].mid(1, 5).contains(num)) {
                    int position = num_total[loop_ana].mid(1, 5).indexOf(num);
                    temp[num_total[loop_ana - 1][66 + position] - 1] += 1;
                    qDebug() << collection_zdbd;
                }
            }

            // temp 排序
            VectorDesc(temp);
            int position = temp.indexOf(num_total[num_now][65 + loop5]) + 1;
            temp.fill(0);
            num_total[num_now] << position;
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

int AnalysisUtils::ZD_ANA(QVector<int> area, int n1, int n2, int n3, int n4, int n5)
{
    // 分3区 4 4 3
    QVector<int> zd_1 = area.mid(0,4);
    QVector<int> zd_2 = area.mid(4,4);
    QVector<int> zd_3 = area.mid(8,3);

    int count_area_1 = zd_1.count(n1) + zd_1.count(n2) + zd_1.count(n3) + zd_1.count(n4) + zd_1.count(n5);
    int count_area_2 = zd_2.count(n1) + zd_2.count(n2) + zd_2.count(n3) + zd_2.count(n4) + zd_2.count(n5);
    int count_area_3 = zd_3.count(n1) + zd_3.count(n2) + zd_3.count(n3) + zd_3.count(n4) + zd_3.count(n5);

    int zd = count_area_1 * 100 + count_area_2 * 10 + count_area_3;
    return DataAll::dic_desc_num[zd];
}

int AnalysisUtils::BD_ANA(QVector<int> area1, QVector<int> area2, QVector<int> area3, QVector<int> area4, QVector<int> area5, int num)
{
    QVector<int> a1;
    QVector<int> a2;
    QVector<int> a3;
    a1 << area1.mid(0,4) << area2.mid(0,4) << area3.mid(0,4) << area4.mid(0,4) << area5.mid(0,4);
    a2 << area1.mid(4,4) << area2.mid(4,4) << area3.mid(4,4) << area4.mid(4,4) << area5.mid(4,4);
    a3 << area1.mid(8,3) << area2.mid(8,3) << area3.mid(8,3) << area4.mid(8,3) << area5.mid(8,3);

    int bd = a1.count(num) * 100 + a2.count(num) * 10 + a3.count(num);
    return DataAll::dic_desc_num[bd];
}

















