//
// Created by bian on 2017/7/7.
//
#include <mem.h>
#include "MPSTD.h"

int getLenOfMatchRowByPoint(char * track, trackSet * Tc){
    int i,j,flag;
    int count = 0;
    for(i=0;i<Tc->count;i++){
        flag = 0;
        for(j=0;j<Tc->trackCollection[i]->count;j++){
            if(strcmp(Tc->trackCollection[i]->tracks[j],track) == 0){
                flag = 1;
            }
        }
        if(flag)
            count ++;
    }
    return count;
}

float caculatePssOfPoint(char * track, trackRow * row, trackSet * Tc, database *db){
    int i;
    database * matched = matchRowByTrajectory(db,row->tracks,row->count);
    float result = 0;
    float p_level_sum = 0;
    int row_len = getLenOfMatchRowByPoint(track,Tc);    // 分子
    int den = getLengthOfDB(matched);
    for(i=0;i<row_count;i++){
        if(db[i] == NULL)
            continue;

        if(db[i]->p_level != -1){       // 去除no privacy
            p_level_sum += db[i]->p_level;
        }
    }
    result = ((float)row_len / (float)den) * p_level_sum;

    return result;
}

float caculatePssOfRow(trackRow * row, trackSet * Tc, database * db){
    float result = 0;
    float val;
    int i;
    for(i=0;i<row->count;i++){
        val = caculatePssOfPoint(row->tracks[i],row,Tc,db);
        result = val > result ? val : result;
    }
    return result;
}

trackRow * getMaxPssRow(trackSet * Tc, database * db){
    int i;
    trackRow * result = NULL;
    float val,max = 0;
    for(i=0;i<Tc->count;i++){
        val = caculatePssOfRow(Tc->trackCollection[i],Tc,db);
        if(max < val){
            result = Tc->trackCollection[i];
        }
        max = max > val ? max : val;
    }
    return result;
}

char * getMaxPssPoint(trackRow * row, trackSet * Tc, database * db){
    int i;
    char * result = NULL;
    float val,max = 0;
    for(i=0;i<row->count;i++){
        val = caculatePssOfPoint(row->tracks[i],row,Tc,db);
        if(max < val){
            result = row->tracks[i];
        }
        max = max > val ? max : val;
    }
    return result;
}

database * mpstd(database * OriginDB, treeNode * root, database * Ts, trackSet * A, float PbThreshold, int maxDepth,
                 int breakFlag, int (*breakFunc)(char *, trackSet *, database *)){
    trackSet *Tc = trackSetInit();
    database * Bj, * Cj, *matched, *Tg, *Cz, *Dz, *ri, *matchedTemp;
    trackRow * tz;
    char * pzq;

    int i,j,k,l;
    int flag;   // 判断rk guarding node是否在最上层
    for(i=0;i<A->count;i++){
        // 3
        matched = matchRowByTrajectory(Ts,A->trackCollection[i]->tracks,A->trackCollection[i]->count);
        Bj = initDb();
        for(j=0;j<row_count - 1;j++){
            if(matched[j] == NULL)
                continue;

            flag = 1;
            for(k=0;k<row_count - 1;k++){
                if(matched[k] == NULL)
                    continue;

                if(nodeAisCoveredByNodeB(root,getGuardingNodeByRow(OriginDB,root,matched[j]->id),getGuardingNodeByRow(OriginDB,root,matched[k]->id))){
                    flag = 0;
                    break;
                }
            }

            if(flag){
                insertRow(Bj,matched[j]->id,matched[j]->p_level,matched[j]->trajectory,matched[j]->trajectoryCount,matched[j]->disease);
            }
        }

        // 4
        Cj = initDb();
        for(j=0;j<row_count;j++){
            if(Bj[j] == NULL)
                continue;

            if(caculateBreachProbability(OriginDB,Ts,root,Bj[j]->id,A->trackCollection[i]->tracks,A->trackCollection[i]->count) > PbThreshold){
                insertRow(Cj,Bj[j]->id,Bj[j]->p_level,Bj[j]->trajectory,Bj[j]->trajectoryCount,Bj[j]->disease);
            }
        }

        // 5 - 6
        if(getLengthOfDB(Cj) != 0){
            insertToSet(Tc,A->trackCollection[i]);
        }
    }

    // 9
    while(Tc->count != 0){
        // 10 - 11
        // todo tz和pzq有可能是集合 ...
        tz = getMaxPssRow(Tc,Ts);
        Cz = initDb();
        matched = matchRowByTrajectory(Ts,tz->tracks,tz->count);
        for(i=0;i<row_count-1;i++){
            if(matched[i] == NULL)
                continue;

            if(caculateBreachProbability(OriginDB,Ts,root,matched[i]->id,tz->tracks,tz->count) > PbThreshold){
                insertRow(Cz,matched[i]->id,matched[i]->p_level,matched[i]->trajectory,matched[i]->trajectoryCount,matched[i]->disease);
            }
        }

        // 12 - 13
        pzq = getMaxPssPoint(tz, Tc, Ts);
        Dz = initDb();

        while (getLengthOfDB(Cz) != 0) {
            traverseDb(Cz,printRow);
            // 15
            ri = initDb();
            int max_p_level = 0;
            for (i = 0; i < row_count - 1; i++) {
                if (Cz[i] == NULL)
                    continue;

                if (Cz[i]->p_level >= max_p_level) {
                    max_p_level = Cz[i]->p_level;
                    insertRow(ri, Cz[i]->id, Cz[i]->p_level, Cz[i]->trajectory, Cz[i]->trajectoryCount, Cz[i]->disease);
                }
            }

            // 16 - 17
            Dz = DBUnion(Dz, ri);
            Ts = DBSub(Ts, ri);

            // 18
            for (j = 0; j < row_count - 1; j++) {
                if (ri[j] == NULL)
                    continue;

                for (k = 0; k < ri[j]->trajectoryCount; k++) {
                    if (strcmp(ri[j]->trajectory[k], pzq) == 0) {
                        // 覆盖第k个
                        for (l = k; l < (ri[j]->trajectoryCount - 1 - k); l++) {
                            ri[j]->trajectory[l] = ri[j]->trajectory[l + 1];
                        }
                        ri[j]->trajectoryCount--;
                    }
                }
            }

            // 19
            Ts = DBUnion(Ts, ri);

            // 20
            Cz = initDb();
            matchedTemp = matchRowByTrajectory(Ts,tz->tracks,tz->count);
            for (j = 0; j < row_count - 1; j++) {
                if (matchedTemp[j] == NULL)
                    continue;

                if (caculateBreachProbability(OriginDB, Ts, root, matchedTemp[j]->id, tz->tracks, tz->count) > PbThreshold) {
                    insertRow(Cz, matchedTemp[j]->id, matchedTemp[j]->p_level, matchedTemp[j]->trajectory, matchedTemp[j]->trajectoryCount, matchedTemp[j]->disease);
                }
            }
        }

        if(breakFlag){
            breakFlag = breakFunc(pzq,Tc,Ts);
        }

        // 22 - 24
        for(i=0;i<row_count-1;i++){
            if(Dz[i] == NULL)
                continue;

            // mcst
            trackSet * set_temp = mcst(OriginDB,root,Ts,tz,pzq,PbThreshold,maxDepth);
            for(j=0;j<set_temp->count;j++){
                insertToSet(Tc,set_temp->trackCollection[j]);
            }
        }

        // 25
        for(i=0;i<Tc->count;i++){
            if(tz == Tc->trackCollection[i]){
                for(j=i;j<(Tc->count - 1 - i);j++){
                    Tc->trackCollection[j] = Tc->trackCollection[j+1];
                }
                Tc->count--;
            }
        }
    }

    Tg = Ts;
    return Tg;
}