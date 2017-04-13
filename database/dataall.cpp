#include "dataall.h"
#include "netnumbers.h"

DataAll::DataAll(QObject *parent) : QObject(parent)
{

}

void DataAll::InitMap()
{
    DataAll::dic_desc_num[5] = 1;
    DataAll::dic_desc_num[14] = 2;
    DataAll::dic_desc_num[23] = 3;
    DataAll::dic_desc_num[32] = 4;
    DataAll::dic_desc_num[41] = 5;
    DataAll::dic_desc_num[50] = 6;
    DataAll::dic_desc_num[104] = 7;
    DataAll::dic_desc_num[113] = 8;
    DataAll::dic_desc_num[122] = 9;
    DataAll::dic_desc_num[131] = 10;
    DataAll::dic_desc_num[140] = 11;
    DataAll::dic_desc_num[203] = 12;
    DataAll::dic_desc_num[212] = 13;
    DataAll::dic_desc_num[221] = 14;
    DataAll::dic_desc_num[230] = 15;
    DataAll::dic_desc_num[302] = 16;
    DataAll::dic_desc_num[311] = 17;
    DataAll::dic_desc_num[320] = 18;
    DataAll::dic_desc_num[401] = 19;
    DataAll::dic_desc_num[410] = 20;
    DataAll::dic_desc_num[500] = 21;

    DataAll::dic_num_desc[1] = 5;
    DataAll::dic_num_desc[2] = 14;
    DataAll::dic_num_desc[3] = 23;
    DataAll::dic_num_desc[4] = 32;
    DataAll::dic_num_desc[5] = 41;
    DataAll::dic_num_desc[6] = 50;
    DataAll::dic_num_desc[7] = 104;
    DataAll::dic_num_desc[8] = 113;
    DataAll::dic_num_desc[9] = 122;
    DataAll::dic_num_desc[10] = 131;
    DataAll::dic_num_desc[11] = 140;
    DataAll::dic_num_desc[12] = 203;
    DataAll::dic_num_desc[13] = 212;
    DataAll::dic_num_desc[14] = 221;
    DataAll::dic_num_desc[15] = 230;
    DataAll::dic_num_desc[16] = 302;
    DataAll::dic_num_desc[17] = 311;
    DataAll::dic_num_desc[18] = 320;
    DataAll::dic_num_desc[19] = 401;
    DataAll::dic_num_desc[20] = 410;
    DataAll::dic_num_desc[21] = 500;
}

QVector<QVector<int>> DataAll::numbers_all;
QMap<int,int> DataAll::dic_desc_num;
QMap<int,int> DataAll::dic_num_desc;
