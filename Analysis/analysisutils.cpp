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

    // 清空数据
    DataAll::numbers_ana.clear();

    // 存放 1-11 的出现次数
    QVector<int> vector_temp(11);

    // 存储一期5个号码的分析结果集合
    QVector<int> vector_temp_group;

    // num_now 正在分析的号码行号
    for (int num_now = num_total.length() - num_ana; num_now < num_total.length(); ++num_now) {

        // 清空临时 vector
        vector_temp_group.clear();
        vector_temp_group << num_total[num_now].mid(0, 6);

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
            vector_temp_group << vector_temp;

        }

        // 保存数据
        DataAll::numbers_ana << vector_temp_group;
    }

    // DataAll::numbers_ana 存储到数据库中
    DataAll::ana_to_database();
}

/**
 * @brief AnalysisUtils::s2_zdbd 第二步: 根据开奖号码计算得到 zdbd 主动和别动,添加到开奖号码后面
 */
void AnalysisUtils::s2_zdbd()
{
    // 清空数据
    DataAll::numbers_zdbd.clear();

    QVector<int> vector_temp_group;

    // 循环分析号码(包含跟随表的数据), 不包含最后一期,因为最后一期没有下一期的结果
    for (int num_now = 0; num_now < DataAll::numbers_ana.length() - 1; ++num_now) {

        // 临时数据清空
        vector_temp_group.clear();
        vector_temp_group << DataAll::numbers_ana[num_now].mid(0, 6);
        vector_temp_group << DataAll::numbers_ana[num_now + 1].mid(1, 5);

        // 分析的号码的下一期号码
        int num_next1 = DataAll::numbers_ana[num_now + 1][1];
        int num_next2 = DataAll::numbers_ana[num_now + 1][2];
        int num_next3 = DataAll::numbers_ana[num_now + 1][3];
        int num_next4 = DataAll::numbers_ana[num_now + 1][4];
        int num_next5 = DataAll::numbers_ana[num_now + 1][5];

        // zd abcde
        QVector<int> desc_a = DataAll::numbers_ana[num_now].mid(6,11);
        QVector<int> desc_b = DataAll::numbers_ana[num_now].mid(17,11);
        QVector<int> desc_c = DataAll::numbers_ana[num_now].mid(28,11);
        QVector<int> desc_d = DataAll::numbers_ana[num_now].mid(39,11);
        QVector<int> desc_e = DataAll::numbers_ana[num_now].mid(50,11);

        // 主动计算
        int trans_int = ZD_ANA(desc_a, num_next1, num_next2, num_next3, num_next4, num_next5);
        vector_temp_group << trans_int;
        trans_int = ZD_ANA(desc_b, num_next1, num_next2, num_next3, num_next4, num_next5);
        vector_temp_group << trans_int;
        trans_int = ZD_ANA(desc_c, num_next1, num_next2, num_next3, num_next4, num_next5);
        vector_temp_group << trans_int;
        trans_int = ZD_ANA(desc_d, num_next1, num_next2, num_next3, num_next4, num_next5);
        vector_temp_group << trans_int;
        trans_int = ZD_ANA(desc_e, num_next1, num_next2, num_next3, num_next4, num_next5);
        vector_temp_group << trans_int;

        // 被动计算
        trans_int = BD_ANA(desc_a, desc_b, desc_c, desc_d, desc_e, num_next1);
        vector_temp_group << trans_int;
        trans_int = BD_ANA(desc_a, desc_b, desc_c, desc_d, desc_e, num_next2);
        vector_temp_group << trans_int;
        trans_int = BD_ANA(desc_a, desc_b, desc_c, desc_d, desc_e, num_next3);
        vector_temp_group << trans_int;
        trans_int = BD_ANA(desc_a, desc_b, desc_c, desc_d, desc_e, num_next4);
        vector_temp_group << trans_int;
        trans_int = BD_ANA(desc_a, desc_b, desc_c, desc_d, desc_e, num_next5);
        vector_temp_group << trans_int;

        // 保存数据
        DataAll::numbers_zdbd << vector_temp_group;

    }

    // DataAll::numbers_zdbd 存储到数据库中
    DataAll::zdbd_to_database();
}

/**
 * @brief AnalysisUtils::s3_zdbd_ana 第三步: 根据本期号码、开奖号码、主动、被动和 num_chart 计算得出规律(主动单,主动整,被动单,被动整)
 *  DataAll::numbers_zdbd 数据结构
 *  内层 QVector 结构: QVector<int>(21)
 *  (0, 6) 期号, 第一个号码, 第二个号码, 第三个号码, 第四个号码, 第五个号码
 *  (6, 5) 下一期的5个号码
 *  (11, 5) 主动表
 *  (16, 5) 被动表
 * @param num_chart 显示的图表期数
 */
void AnalysisUtils::s3_zdbd_ana(const int num_chart)
{

    // 临时存储个数的 QVector 1-21
    QVector<int> temp(21);

    // 清空数据
    DataAll::numbers_chart.clear();

    QVector<int> vector_temp_group;

    // 循环 最后的 num_chart 期数据, 不包含最后的一期
    for (int num_now = DataAll::numbers_zdbd.length() - num_chart; num_now < DataAll::numbers_zdbd.length(); ++num_now) {

        // 清空临时数组
        temp.fill(0);

        // 临时数据清空
        vector_temp_group.clear();
        // vector_temp_group 存储号码
        vector_temp_group << DataAll::numbers_zdbd[num_now].mid(0, 6);

        // 主动单
        // 循环 1-5 个号码
        for (int loop5 = 1; loop5 <= 5; ++loop5) {
            int num = DataAll::numbers_zdbd[num_now][loop5];
            for (int loop_ana = 0; loop_ana < num_now; ++loop_ana) {
                if (DataAll::numbers_zdbd[loop_ana].mid(1, 5).contains(num)) {
                    int pos = DataAll::numbers_zdbd[loop_ana].mid(1,5).indexOf(num);
                    int v = DataAll::numbers_zdbd[loop_ana][10 + pos];
                    temp[v - 1] += 1;
                }
            }

            // temp 排序
            VectorDesc(temp);
            int position = temp.indexOf(DataAll::numbers_zdbd[num_now][10 + loop5]) + 1;
            temp.fill(0);
            // vector_temp_group 存储号码 + 主动计算结果
            vector_temp_group << position;
        }

        // 被动单
        // 目标: 被动单: 多出5个数字 pointer(76-80)
        // 循环 1-5 个号码
        for (int loop5 = 1; loop5 <= 5; ++loop5) {
            int num = DataAll::numbers_zdbd[num_now][loop5 + 5];
            for (int loop_ana = 0; loop_ana < num_now; ++loop_ana) {
                if (DataAll::numbers_zdbd[loop_ana].mid(6, 5).contains(num)) {
                    temp[DataAll::numbers_zdbd[loop_ana][loop5 + 15] - 1] += 1;
                }
            }

            // temp 排序
            VectorDesc(temp);
            int position = temp.indexOf(DataAll::numbers_zdbd[num_now][15 + loop5]) + 1;
            temp.fill(0);
            // vector_temp_group 存储号码 + 主动计算结果 + 被动计算结果
            vector_temp_group << position;
        }


        // 主动整
        // 循环 1-5 个号码
        for (int loop5 = 1; loop5 <= 5; ++loop5) {
            for (int loop_ana = 0; loop_ana < num_now; ++loop_ana) {
                temp[DataAll::numbers_zdbd[loop_ana][11] - 1] += 1;
                temp[DataAll::numbers_zdbd[loop_ana][12] - 1] += 1;
                temp[DataAll::numbers_zdbd[loop_ana][13] - 1] += 1;
                temp[DataAll::numbers_zdbd[loop_ana][14] - 1] += 1;
                temp[DataAll::numbers_zdbd[loop_ana][15] - 1] += 1;
            }

            // temp 排序
            VectorDesc(temp);
            int position = temp.indexOf(DataAll::numbers_zdbd[num_now][10 + loop5]) + 1;
            temp.fill(0);
            // vector_temp_group 存储号码 + 主动计算结果
            vector_temp_group << position;
        }

        // 被动整
        // 目标: 被动单: 多出5个数字 pointer(76-80)
        // 循环 1-5 个号码
        for (int loop5 = 1; loop5 <= 5; ++loop5) {
            for (int loop_ana = 0; loop_ana < num_now; ++loop_ana) {
                temp[DataAll::numbers_zdbd[loop_ana][16] - 1] += 1;
                temp[DataAll::numbers_zdbd[loop_ana][17] - 1] += 1;
                temp[DataAll::numbers_zdbd[loop_ana][18] - 1] += 1;
                temp[DataAll::numbers_zdbd[loop_ana][19] - 1] += 1;
                temp[DataAll::numbers_zdbd[loop_ana][20] - 1] += 1;
            }

            // temp 排序
            VectorDesc(temp);
            int position = temp.indexOf(DataAll::numbers_zdbd[num_now][15 + loop5]) + 1;
            temp.fill(0);
            // vector_temp_group 存储号码 + 主动计算结果 + 被动计算结果
            vector_temp_group << position;
        }

        // 保存数据
        DataAll::numbers_chart << vector_temp_group;
    }

    // DataAll::numbers_chart 存储到数据库中
    DataAll::chart_to_database();
}

/**
 * @brief AnalysisUtils::s4_filter void 第四步: 过滤号码
 * @param zdd QVector<int> 主动单的过滤条件, 1-21 的集合
 * @param zdz QVector<int> 主动整的过滤条件, 1-21 的集合
 * @param bdd QVector<int> 被动单的过滤条件, 1-21 的集合
 * @param bdz QVector<int> 被动整的过滤条件, 1-21 的集合
 */
void AnalysisUtils::s4_filter(const QVector<int> zdd, const QVector<int> zdz, const QVector<int> bdd, const QVector<int> bdz)
{
    // 获取 DataAll::numbers_ana 的最后一期的数据
    QVector<int> last = DataAll::numbers_ana[DataAll::numbers_ana.length() - 1];
//    qDebug() << "最后一期的 numbers_ana 数据是:";
//    qDebug() << "期号: " << last[0];
//    qDebug() << "号码: " << last.mid(1,5);
//    qDebug() << "第1个号码的 DESC: " << last.mid(6,11);
//    qDebug() << "第2个号码的 DESC: " << last.mid(17,11);
//    qDebug() << "第3个号码的 DESC: " << last.mid(28,11);
//    qDebug() << "第4个号码的 DESC: " << last.mid(39,11);
//    qDebug() << "第5个号码的 DESC: " << last.mid(50,11);

    // 过滤结果 QVector<int>
    DataAll::init_numbers_filter();

    // 循环 DataAll::numbers_filter (现在的格式是: QVector<int>(5) 长度为462)
    for (int var = 0; var < DataAll::numbers_filter.length(); ++var) {
        // zd
        int temp_zdbd = AnalysisUtils::ZD_ANA(last.mid(6, 11), DataAll::numbers_filter[var][0],
                DataAll::numbers_filter[var][1], DataAll::numbers_filter[var][2],
                DataAll::numbers_filter[var][3], DataAll::numbers_filter[var][4]);
        DataAll::numbers_filter[var] << temp_zdbd;

        temp_zdbd = AnalysisUtils::ZD_ANA(last.mid(17, 11), DataAll::numbers_filter[var][0],
                DataAll::numbers_filter[var][1], DataAll::numbers_filter[var][2],
                DataAll::numbers_filter[var][3], DataAll::numbers_filter[var][4]);
        DataAll::numbers_filter[var] << temp_zdbd;

        temp_zdbd = AnalysisUtils::ZD_ANA(last.mid(28, 11), DataAll::numbers_filter[var][0],
                DataAll::numbers_filter[var][1], DataAll::numbers_filter[var][2],
                DataAll::numbers_filter[var][3], DataAll::numbers_filter[var][4]);
        DataAll::numbers_filter[var] << temp_zdbd;

        temp_zdbd = AnalysisUtils::ZD_ANA(last.mid(39, 11), DataAll::numbers_filter[var][0],
                DataAll::numbers_filter[var][1], DataAll::numbers_filter[var][2],
                DataAll::numbers_filter[var][3], DataAll::numbers_filter[var][4]);
        DataAll::numbers_filter[var] << temp_zdbd;

        temp_zdbd = AnalysisUtils::ZD_ANA(last.mid(50, 11), DataAll::numbers_filter[var][0],
                DataAll::numbers_filter[var][1], DataAll::numbers_filter[var][2],
                DataAll::numbers_filter[var][3], DataAll::numbers_filter[var][4]);
        DataAll::numbers_filter[var] << temp_zdbd;

        // bd
        temp_zdbd = AnalysisUtils::BD_ANA(last.mid(6, 11), last.mid(17, 11), last.mid(28, 11),
                                          last.mid(39, 11), last.mid(50, 11), DataAll::numbers_filter[var][0]);
        DataAll::numbers_filter[var] << temp_zdbd;

        temp_zdbd = AnalysisUtils::BD_ANA(last.mid(6, 11), last.mid(17, 11), last.mid(28, 11),
                                          last.mid(39, 11), last.mid(50, 11), DataAll::numbers_filter[var][1]);
        DataAll::numbers_filter[var] << temp_zdbd;

        temp_zdbd = AnalysisUtils::BD_ANA(last.mid(6, 11), last.mid(17, 11), last.mid(28, 11),
                                          last.mid(39, 11), last.mid(50, 11), DataAll::numbers_filter[var][2]);
        DataAll::numbers_filter[var] << temp_zdbd;

        temp_zdbd = AnalysisUtils::BD_ANA(last.mid(6, 11), last.mid(17, 11), last.mid(28, 11),
                                          last.mid(39, 11), last.mid(50, 11), DataAll::numbers_filter[var][3]);
        DataAll::numbers_filter[var] << temp_zdbd;

        temp_zdbd = AnalysisUtils::BD_ANA(last.mid(6, 11), last.mid(17, 11), last.mid(28, 11),
                                          last.mid(39, 11), last.mid(50, 11), DataAll::numbers_filter[var][4]);
        DataAll::numbers_filter[var] << temp_zdbd;

    }

//    qDebug() << "DataAll::numbers_filter 的全部数据:";
//    foreach (QVector<int> temp, DataAll::numbers_filter) {
//        qDebug() << "号码: " << temp.mid(0, 5);
//        qDebug() << "zd : " << temp.mid(5, 5);
//        qDebug() << "bd : " << temp.mid(10, 5);
//    }

    // DataAll::numbers_zdbd 最后一期排序
    // DataAll::numbers_zdbd 内层 QVector 结构: QVector<int>(21)
    // (0, 6) 期号, 第一个号码, 第二个号码, 第三个号码, 第四个号码, 第五个号码 (不包含最后一期)
    // (6, 5) 下一期的5个号码
    // (11, 5) 主动表
    // (16, 5) 被动表

    // 最后一期的 5 个号码
    QVector<int> last_num = last.mid(1, 5);

    // 计算 last_num 的第一个号码的主动单 DESC
    QVector<int> last_zdd(21);
    last_zdd.fill(0);
    for (int var = 0; var < DataAll::numbers_zdbd.length() - 1; ++var) {
        QVector<int> temp = DataAll::numbers_zdbd[var].mid(1,5);
        if(temp.contains(last_num[0])){
            int pos = temp.indexOf(last_num[0]) + 1;
            int v = DataAll::numbers_zdbd[var][11 + pos];
            last_zdd[v - 1] += 1;
        }
    }
    VectorDesc(last_zdd);


    // 计算 last_num 的第一个号码的主动整 DESC
    QVector<int> last_zdz(21);
    last_zdz.fill(0);
    for (int var = 0; var < DataAll::numbers_zdbd.length() - 1; ++var) {
        int v = DataAll::numbers_zdbd[var][11];
        last_zdz[v - 1] += 1;
        v = DataAll::numbers_zdbd[var][12];
        last_zdz[v - 1] += 1;
        v = DataAll::numbers_zdbd[var][13];
        last_zdz[v - 1] += 1;
        v = DataAll::numbers_zdbd[var][14];
        last_zdz[v - 1] += 1;
        v = DataAll::numbers_zdbd[var][15];
        last_zdz[v - 1] += 1;
    }
    VectorDesc(last_zdz);

    // 计算 last_num 的第一个号码的被动单 DESC
    QMap<int, QVector<int>> bdd_map;
    QVector<int> temp_vector(21);
    for (int var11 = 1; var11 <= 11; ++var11) {
        // 临时数组清空数据
        temp_vector.fill(0);

//        for (int var = 0; var < DataAll::numbers_zdbd.length() - 1; ++var) {
//            QVector<int> temp = DataAll::numbers_zdbd[var].mid(1,5);
//            if(temp.contains(last_num[0])){
//                int pos = temp.indexOf(last_num[0]) + 1;
//                int v = DataAll::numbers_zdbd[var][11 + pos];
//                last_zdd[v - 1] += 1;
//            }
//        }
        // DESC
        VectorDesc(temp_vector);
        // 保存结果集
        bdd_map[var11] = temp_vector;
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

















