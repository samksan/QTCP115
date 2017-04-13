#ifndef ANALYSISUTILS_H
#define ANALYSISUTILS_H

#include <QObject>
#include <QVector>

/**
 * @brief The AnalysisUtils class
 * 分析工具集
 */
class AnalysisUtils : public QObject
{
    Q_OBJECT
public:
    explicit AnalysisUtils(QObject *parent = 0);

    // 第一步: 循环计算得出跟随表
    static void s1_follow(QVector<QVector<int>> &num_total, const int num_base, const int num_ana);

    // 第二步: 根据跟随表和开奖号码计算得到 主动 被动 代码
    static void s2_zdbd(QVector<QVector<int>> &num_total, const int num_ana);
private:
    /**
     * @brief VectorDesc 修改传入的 QVector, 变成 1-11 的出现次数的多少排序DESC
     * @param vector 11个号码的出现次数
     */
    static void VectorDesc(QVector<int> &vector);

    /**
     * @brief ZD_ANA 主动计算
     * @param area QVector<int> 表示1-11 的DESC排序
     * @param n1 号码1
     * @param n2 号码2
     * @param n3 号码3
     * @param n4 号码4
     * @param n5 号码5
     * @return 主动值
     */
    static int ZD_ANA(QVector<int> area, int n1, int n2, int n3, int n4, int n5);

    /**
     * @brief BD_ANA 被动计算
     * @param area1 QVector<int> desc 一区
     * @param area2 QVector<int> desc 二区
     * @param area3 QVector<int> desc 三区
     * @param area4 QVector<int> desc 四区
     * @param area5 QVector<int> desc 五区
     * @param num 号码
     * @return 被动值
     */
    static int BD_ANA(QVector<int> area1, QVector<int> area2, QVector<int> area3, QVector<int> area4, QVector<int> area5, int num);

signals:

public slots:
};

#endif // ANALYSISUTILS_H
