//
// Created by bian on 2017/7/8.
//

#ifndef PPTD_SAGTD_PRINT_H
#define PPTD_SAGTD_PRINT_H
#include "../SAGTD/SAGTD.h"
#include "../MPSTD/MPSTD.h"

// SAGTD逐步打印函数
int SAGTDBreakFunc(database * Bj, database *Cj,  database * T, float PbThreshold, int maxDepth, trackRow * attack_row);

// SAGTD不逐步打印函数
int SAGTDNonBreakFunc(database * Bj, database *Cj,  database * T, float PbThreshold, int maxDepth, trackRow * attack_row);

// 得到用户选择
int SAGTDChoice();

// SAGTD算法演示主函数
database * SAGTDFunc(database * originDB,treeNode * root,database * db, int maxDepth, float PbThreshold);

#endif //PPTD_SAGTD_PRINT_H
