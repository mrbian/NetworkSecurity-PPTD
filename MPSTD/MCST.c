//
// Created by bian on 2017/7/7.
//
#include <mem.h>
#include "MCST.h"

// mcst第10行得到pzq在tz中的idx
int getIdxOfpzq(trackRow * tz, char *pzq){
    int i,idx=-1;
    for(i=0;i<tz->count;i++){
        if(strcmp(tz->tracks[i],pzq) == 0){
            idx = i;
        }
    }
    return idx;
}

trackSet * mcst(database * originDB, treeNode * root, database * Ts, trackRow * tz, char * pzq, float PbThreshold, int maxDepth){
    trackSet ** ASetArr;
    ASetArr = (trackSet **)malloc(sizeof(trackSet *) * (maxDepth + 1));
    int i,j,k;
    int flag;   // 判断是否某些行的泄露概率大于阈值
    int len;    // tk 长度

    // 1
    trackSet * Tc = trackSetInit();
    // 2
    trackSet * A1 = trackSetInit();
    char * trset[1] = {pzq};
    trackRow * tr = initOneRow(trset,1);
    insertToSet(A1,tr);

    i = 1;
    ASetArr[i-1] = A1;
    // 4 - 12
    while(i<=maxDepth && (ASetArr[i-1]->count != 0)){
        // 5 - 9
        for(j=0;j<ASetArr[i-1]->count;j++){
            flag = 0;
            for(k=0;k<row_count-1;k++){
                if(Ts[k] == NULL)
                    continue;

                if(caculateBreachProbability(originDB,Ts,root,Ts[k]->id,tz->tracks,tz->count) > PbThreshold){
                    flag = 1;
                }
            }

            if(flag){
                insertToSet(Tc,ASetArr[i-1]->trackCollection[j]);
            }
        }

        // 10
        ASetArr[i] = trackSetInit();
        len = i + 1;
        trackRow * r_temp;
        if((getIdxOfpzq(tz,pzq) <= len) && (tz->count >= len)){
            r_temp = initOneRow(tz->tracks,len);
            insertToSet(ASetArr[i],r_temp);
        }
        i ++;

    }

    return Tc;
}
