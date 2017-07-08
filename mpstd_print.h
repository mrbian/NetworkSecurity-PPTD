//
// Created by bian on 2017/7/8.
//

#ifndef PPTD_MPSTD_PRINT_H
#define PPTD_MPSTD_PRINT_H

#include "SAGTD/SAGTD.h"
#include "MPSTD/MPSTD.h"

database * MPSTDFunc(database * originDB,treeNode * root,database * db, trackSet *A, int maxDepth, float PbThreshold);

#endif //PPTD_MPSTD_PRINT_H
