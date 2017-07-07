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

#define maxDepth 2

database * SAGTD(database * originDB, treeNode* root, int MaxSetNum,float PbThreshold);

#endif //PPTD_SAGTD_H
