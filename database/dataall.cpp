#include "dataall.h"
#include "netnumbers.h"

DataAll::DataAll(QObject *parent) : QObject(parent)
{

}

QVector<QVector<int>> DataAll::numbers_all;
