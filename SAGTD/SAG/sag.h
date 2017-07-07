//
// Created by bian on 2017/7/6.
//

#ifndef PPTD_SAG_H
#define PPTD_SAG_H

#include <stdio.h>
#include "../../Database/database.h"
#include "../../Tree/tree.h"
#include "../common/common.h"
#include "../STR/str.h"

// 行是否在Db内
bool isInDb(database * db, row * row);

// 数据库相减
database * DBSub(database * minuend, database * subtracted);

// 数据库并集
database * DBUnion(database * db1, database *db2);

// 泛化属性时修改全局db
void changeDbRowSensitiveValue(database *db, int rowId, char * disease);

database * sag(database * originDB, database * db, treeNode * root, trackRow * background, database * Cj, int maxDepth, float PbThreshold);

#endif //PPTD_SAG_H
