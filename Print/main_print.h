//
// Created by bian on 2017/7/16.
//

#ifndef PPTD_MAIN_PRINT_H
#define PPTD_MAIN_PRINT_H

#include "stdio.h"
#include "../SAGTD/SAGTD.h"
#include "../MPSTD/MPSTD.h"
#include "sagtd_print.h"
#include "mpstd_print.h"

int inputChoice();

void caculateFunc(database * originDB,treeNode * root, database *db);

void main_thread(database * originDB,treeNode * root,database * db);

#endif //PPTD_MAIN_PRINT_H
