//
// Created by bian on 2017/7/7.
//

#ifndef PPTD_MCST_H
#define PPTD_MCST_H

#include "../SAGTD/SAGTD.h"

trackSet * mcst(database * originDB, treeNode * root, database * Ts, trackRow * tz, char * pzq, float PbThreshold);

#endif //PPTD_MCST_H
