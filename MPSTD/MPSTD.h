//
// Created by bian on 2017/7/7.
//

#ifndef PPTD_MPSTD_H
#define PPTD_MPSTD_H

#include <stdio.h>
#include "../SAGTD/SAGTD.h"
#include "../SAGTD/common/common.h"
#include "MCST.h"

// 轨迹集合内一个点所匹配到的数目
int getLenOfMatchRowByPoint(char * track, trackSet * Tc);

// 计算一个点的压制分数
float caculatePssOfPoint(char * track, trackRow * row, trackSet * Tc, database *db);

// 计算一条轨迹压制分数（最大值）
float caculatePssOfRow(trackRow * row, trackSet * Tc, database * db);

// 得到最大压制行
trackRow * getMaxPssRow(trackSet * Tc, database * db);

// 得到最大压制点
char * getMaxPssPoint(trackRow * row, trackSet * Tc, database * db);


database * mpstd(database * OriginDB, treeNode * root, database * Ts, trackSet * A, float PbThreshold, int maxDepth);

#endif //PPTD_MPSTD_H
