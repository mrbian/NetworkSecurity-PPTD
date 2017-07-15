//
// Created by bian on 2017/7/5.
//

#ifndef PPTD_STR_H
#define PPTD_STR_H
#include <stdio.h>
#include "../../Database/database.h"
#include "../common/common.h"
#include "../../config/config.h"
#include "../../TrackSet/track.h"

// 得到A1
trackSet * getA1FromT(database * db);

void _str_test();

// 返回集合
trackSet * str_main(database * db, int MaxSetNum);

#endif //PPTD_STR_H
