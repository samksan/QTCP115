#ifndef DATAALL_H
#define DATAALL_H

#include <QObject>

class DataAll : public QObject
{
    Q_OBJECT
public:
    explicit DataAll(QObject *parent = 0);

    static void InitMap();

    /**
     * @brief numbers_all QVector<QVector<int>> 开奖号码的集合
     *  内层 QVector 结构: (0, 6)期号, 第一个号码, 第二个号码, 第三个号码, 第四个号码, 第五个号码
     */
    static QVector<QVector<int>> numbers_all;

    /**
     * @brief numbers_ana QVector<QVector<int>> Step1 得出的结果
     *  内层 QVector 结构: QVector<int>(61)
     *  (0, 6)期号, 第一个号码, 第二个号码, 第三个号码, 第四个号码, 第五个号码
     *  (6, 11) 第一个号码的出现次数排序(DESC)
     *  (17, 11) 第一个号码的出现次数排序(DESC)
     *  (28, 11) 第一个号码的出现次数排序(DESC)
     *  (39, 11) 第一个号码的出现次数排序(DESC)
     *  (50, 11) 第一个号码的出现次数排序(DESC)
     */
    static QVector<QVector<int>> numbers_ana;

    static void ana_to_database();

    static void zdbd_to_database();

    /**
     * @brief numbers_zdbd QVector<QVector<int>> Step2 得出的结果, 不包含最后一期号码
     *  内层 QVector 结构: QVector<int>(21)
     *  (0, 6) 期号, 第一个号码, 第二个号码, 第三个号码, 第四个号码, 第五个号码
     *  (6, 5) 下一期的5个号码
     *  (11, 5) 主动表
     *  (16, 5) 被动表
     */
    static QVector<QVector<int>> numbers_zdbd;

    /**
     * @brief numbers_chart QVector<QVector<int>> Step3 得出的结果, 不包含最后一期号码
     *  内层 QVector 结构: QVector<int>(26)
     *  (0, 6) 期号, 第一个号码, 第二个号码, 第三个号码, 第四个号码, 第五个号码
     *  (6, 5) 主动单
     *  (11, 5) 被动单
     *  (16, 5) 主动整
     *  (21, 5) 被动整
     */
    static QVector<QVector<int>> numbers_chart;
    static QMap<int,int> dic_desc_num;
    static QMap<int,int> dic_num_desc;
signals:

public slots:
};

#endif // DATAALL_H
