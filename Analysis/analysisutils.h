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

    static void s1_follow(QVector<QVector<int>> &num_total, const int num_base, const int num_ana);

private:
    /**
     * @brief VectorDesc 修改传入的 QVector, 变成 1-11 的出现次数的多少排序DESC
     * @param vector 11个号码的出现次数
     */
    static void VectorDesc(QVector<int> &vector);

signals:

public slots:
};

#endif // ANALYSISUTILS_H
