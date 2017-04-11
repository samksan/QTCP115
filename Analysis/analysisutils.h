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
signals:

public slots:
};

#endif // ANALYSISUTILS_H
