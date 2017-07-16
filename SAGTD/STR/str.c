//
// Created by bian on 2017/7/5.
//
#include <malloc.h>
#include "str.h"


trackSet * getA1FromT(database * db){
    trackSet * A1 = trackSetInit();

    int i,j;
    struct trackRow * pt;
    for(i=0;i<row_count;i++){
        if(db[i] == NULL)
            continue;

        for(j=0;j<db[i]->trajectoryCount;j++){
            pt = initOneRow(charToPChar(db[i]->trajectory[j]),1);
            insertToSet(A1,pt);
        }
    }
    return A1;
}

// float PbThreshold       // δ
// int MaxSetNum           // σ
trackSet * str_main(database * db, int MaxSetNum){
    int i,j,k;

    // 1 - 2
    trackSet * set = trackSetInit();    // Aδ
    trackSet * A1 = getA1FromT(db);    // A1
    trackSet ** ASetsArr = (trackSet **)malloc(sizeof(trackSet *) * (MaxSetNum + 1));   // Ai
    for(i=0;i<(MaxSetNum+1);i++){
        ASetsArr[i] = NULL;
    }
    ASetsArr[0] = A1;

    // 3 - 6
    for(i=0;i<A1->count;i++){
        insertToSet(set,A1->trackCollection[i]);
    }

    // 7 - 21
    i=1;
    while(i<=MaxSetNum && ASetsArr[i-1] != NULL){
        ASetsArr[i] = trackSetInit();
        trackSet * Atemp = ASetsArr[i-1];

        for(j=1;j<=Atemp->count;j++){
            for(k=j+1;k<=Atemp->count;k++){

                // 12
                /**
                 * 如果两两之间可以联结并且攻击匹配到有相同的行
                 */
                trackRow * joinResult = joinTracks(Atemp->trackCollection[j-1],Atemp->trackCollection[k-1]);
                // todo matchRowBy.. memory
                if( joinResult != NULL && (getLenOfintersectionOfRows(
                        matchRowByTrajectory(db,Atemp->trackCollection[j-1]->tracks,Atemp->trackCollection[j-1]->count),
                        matchRowByTrajectory(db,Atemp->trackCollection[k-1]->tracks,Atemp->trackCollection[k-1]->count)
                ) != 0)){
                    insertToSet(ASetsArr[i],joinResult);
                    insertToSet(set,joinResult);
                }
            }
        }
        i++;
    }

    return set;
}