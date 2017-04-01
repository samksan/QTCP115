#ifndef ANALYSISUTILS_H
#define ANALYSISUTILS_H

#include <QObject>

/**
 * @brief The AnalysisUtils class
 * 分析工具集
 */
class AnalysisUtils : public QObject
{
    Q_OBJECT
public:
    explicit AnalysisUtils(QObject *parent = 0);

    // 开奖号码和购买的方案的对比
    static QVector<QString> NumbersCompare(QString text);

signals:

public slots:
};

#endif // ANALYSISUTILS_H
