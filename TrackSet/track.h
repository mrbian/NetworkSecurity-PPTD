//
// Created by bian on 2017/7/15.
//

#ifndef PPTD_TRACK_H
#define PPTD_TRACK_H

#include <stdio.h>
#include <stdbool.h>
#include <mem.h>
#include "../config/config.h"

// ������ÿһ��Ԫ��
typedef struct trackRow{
    char ** tracks;     //·����
    int count;  // ·���㳤��
}trackRow;

// ����
typedef struct trackSet{
    int count;
    trackRow ** trackCollection;
}trackSet;

// ��ʼ������
trackSet * trackSetInit();

// ����һ�й켣����Row
trackRow * initOneRow(char ** tracks, int count);

// �Ƚ������켣�����Ƿ����
bool cmpTracks(char **t1,int count1, char **t2, int count2);

// һ���켣�����Ƿ��ڼ�����
bool isInSet(trackSet * set, trackRow * row);

// ���ϲ��룬�Զ��ж��Ƿ��ظ�
void insertToSet(trackSet * set, trackRow * tR);

// �켣������
trackRow * joinTracks(trackRow * track1, trackRow * track2);

void _printSetData(trackRow * row);

// print
void printSet(trackRow * row);

// ��������
void traverseSet(trackSet * set, void (*pfunc)(trackRow *));


#endif //PPTD_TRACK_H
