#ifndef DATAALL_H
#define DATAALL_H

#include <QObject>

class DataAll : public QObject
{
    Q_OBJECT
public:
    explicit DataAll(QObject *parent = 0);

    static QVector<QVector<int>> numbers_all;
signals:

public slots:
};

#endif // DATAALL_H
