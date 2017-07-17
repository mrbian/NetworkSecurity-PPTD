//
// Created by bian on 2017/7/16.
//

#ifndef PPTD_ANALYSIS_H
#define PPTD_ANALYSIS_H

#include "malloc.h"
#include "../config/config.h"
#include "../SAGTD/SAGTD.h"
#include "../MPSTD/MPSTD.h"

char* join(char *s1, char *s2);

void appendDatabaseToFile(database * db, char * destFilePath);

void coverDatabaseToFile(database *db, char * destFilePath);

void generateBigDatabase( char * srcFilePath, char * destFilePath, int loopTimes);

void analysis_main();

#endif //PPTD_ANALYSIS_H
