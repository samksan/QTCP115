#ifndef NETNUMBERS_H
#define NETNUMBERS_H

#include <QObject>
#include <QtCore>
#include <QList>

class NetNumbers : public QObject
{
    Q_OBJECT
public:
    static void initQSQLDatabase();
    static void getHtmlFrom360();
    static QVector<QVector<int>> getNumbers();
private:
    static void toDB(int number[100][6]);
};

#endif // NETNUMBERS_H
