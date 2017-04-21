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
    AnalysisUtils::s1_follow(DataAll::numbers_all, num_base, num_ana);

    // 第二步: 根据跟随表和开奖号码计算得到 主动 被动 代码
    AnalysisUtils::s2_zdbd();
    qDebug() << "s2 finished";

    // 第三步: 根据本期号码、开奖号码、主动、被动和 num_chart 计算得出规律(主动单,主动整,被动单,被动整)
    AnalysisUtils::s3_zdbd_ana(num_chart);

    //qDebug() << "s3 finished";


}
