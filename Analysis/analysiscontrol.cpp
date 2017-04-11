#include "analysiscontrol.h"
#include "analysisutils.h"
#include "database/netnumbers.h"
#include <QMessageBox>
#include "database/dataall.h"

AnalysisControl::AnalysisControl(QObject *parent) : QObject(parent)
{

}

/**
 * @brief AnalysisControl::start 控制号码分析流程
 * @param num_base 基础期数
 * @param num_ana 分析号码的期数
 * @param num_chart 显示图标的期数
 */
void AnalysisControl::start(const int num_base, const int num_ana, const int num_chart)
{
    // 第一步: 循环计算得出跟随表
    qDebug() << "lskjflksdj";
    qDebug() << DataAll::numbers_all[0][0];
    AnalysisUtils::s1_follow(DataAll::numbers_all, num_base, num_ana);
    qDebug() << "affffflskjflksdj";
    qDebug() << DataAll::numbers_all[0][0];

}
