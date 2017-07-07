//
// Created by bian on 2017/7/4.
//

#ifndef PPTD_DATABASE_H
#define PPTD_DATABASE_H

#include <stdio.h>
#include <stdbool.h>

#define row_count 7
#define trajectory_item_num 20  // 每一行的轨迹个数最大为20个
#define disease_len 50
#define DB_FILE_PATH_3 "C:\\Users\\bian\\Desktop\\code\\PPTD\\config\\database3.txt"

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

void _db_main();

#endif //PPTD_DATABASE_H
