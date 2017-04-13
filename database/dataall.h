#ifndef DATAALL_H
#define DATAALL_H

#include <QObject>

class DataAll : public QObject
{
    Q_OBJECT
public:
    explicit DataAll(QObject *parent = 0);

    static void InitMap();

    static QVector<QVector<int>> numbers_all;
    static QMap<int,int> dic_desc_num;
    static QMap<int,int> dic_num_desc;
signals:

public slots:
};

#endif // DATAALL_H
