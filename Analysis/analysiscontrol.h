#ifndef ANALYSISCONTROL_H
#define ANALYSISCONTROL_H

#include <QObject>

/**
 * @brief The AnalysisControl class
 * 分析控制器
 */
class AnalysisControl : public QObject
{
    Q_OBJECT
public:
    explicit AnalysisControl(QObject *parent = 0);

    // 控制号码分析流程
    void start(const int num_base, const int num_ana, const int num_chart);

signals:

public slots:
};

#endif // ANALYSISCONTROL_H
