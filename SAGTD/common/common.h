//
// Created by bian on 2017/7/5.
//

#ifndef PPTD_PROBABILITY_H
#define PPTD_PROBABILITY_H
#include <stdio.h>
#include "../../Tree/tree.h"
#include "../../Database/database.h"

// 计算泄露概率
float caculateBreachProbability(database * originDb, database * db,treeNode * root, int rowId, char ** background, int backgroundCount);

// 返回guarding node，注意每一行守护结点泛化前后都不变，所以需要传入originDb
treeNode * getGuardingNodeByRow(database * originDb, treeNode * root, int rowId);

// 得到行的twin node
treeNode * getTwinNodeByRow(treeNode * root, row * row);

// 攻击匹配数据行，即T函数
database * matchRowByTrajectory(database * db, char ** trCollection, int count);

// 返回数据库之间的行交集
database * getIntersectionOfRows(database * db1, database * db2);

// 得到行交集的长度
int getLenOfintersectionOfRows(database * db1, database * db2);

// db 长度
int getLengthOfDB(database * db);

// char * -> char **
char ** charToPChar(char * str);

void _common_main(database * originDB);

#endif //PPTD_PROBABILITY_H