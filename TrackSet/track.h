//
// Created by bian on 2017/7/15.
//

#ifndef PPTD_TRACK_H
#define PPTD_TRACK_H

#include <stdio.h>
#include <stdbool.h>
#include <mem.h>
#include "../config/config.h"

// 集合内每一个元素
typedef struct trackRow{
    char ** tracks;     //路径链
    int count;  // 路径点长度
}trackRow;

// 集合
typedef struct trackSet{
    int count;
    trackRow ** trackCollection;
}trackSet;

// 初始化集合
trackSet * trackSetInit();

// 根据一行轨迹生成Row
trackRow * initOneRow(char ** tracks, int count);

// 比较两个轨迹数组是否相等
bool cmpTracks(char **t1,int count1, char **t2, int count2);

// 一条轨迹数据是否在集合内
bool isInSet(trackSet * set, trackRow * row);

// 集合插入，自动判断是否重复
void insertToSet(trackSet * set, trackRow * tR);

// 轨迹的联结
trackRow * joinTracks(trackRow * track1, trackRow * track2);

void _printSetData(trackRow * row);

// print
void printSet(trackRow * row);

// 遍历集合
void traverseSet(trackSet * set, void (*pfunc)(trackRow *));


#endif //PPTD_TRACK_H
