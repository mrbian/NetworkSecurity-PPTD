//
// Created by bian on 2017/7/4.
//

#ifndef PPTD_DATABASE_H
#define PPTD_DATABASE_H

#include <stdio.h>
#include <stdbool.h>
#include "../config/config.h"

typedef struct row{
    int id;
    int p_level;    // 隐私等级
    char** trajectory;
    int trajectoryCount;
    char disease[disease_len];
}row;

typedef row* database; // 存储指向结构体的指针

database * initDb();

void migrate(database * db,char * filePath);

bool insertRow(database * db,int id,int p_level, char** trajectory, int count, char disease[disease_len]);

void printRow(row * row);

void traverseDb(database *,void (*pfunc)(row *));

row * getRowById(database * db, int id);

// 匹配一个轨迹
database * getRowsByTrajectory(database * db, char * tr);

// 根据Id排序db
void sortDB(database * db);

// 释放DB
void freeDb(database * db);

void _db_main();

#endif //PPTD_DATABASE_H
