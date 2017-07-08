//
// Created by bian on 2017/7/6.
//

#ifndef PPTD_SAGTD_H
#define PPTD_SAGTD_H

#include <stdio.h>
#include "common/common.h"
#include "STR/str.h"
#include "../Tree/tree.h"
#include "SAG/sag.h"

database * SAGTD(database * originDB, database *db ,treeNode* root, int MaxSetNum,float PbThreshold, int maxDepth,
                 int breakFlag, int (*breakFun)(database *, database *, database *, float, int, trackRow *));

#endif //PPTD_SAGTD_H
