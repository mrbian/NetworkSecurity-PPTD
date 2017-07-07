//
// Created by bian on 2017/7/5.
//
#include <malloc.h>
#include <mem.h>
#include "str.h"

trackSet * trackSetInit(){
    trackSet * pset = (trackSet *)malloc(sizeof(trackSet));
    pset->count = 0;
    pset->trackCollection = NULL;
}

trackRow * initOneRow(char ** tracks, int count){
    trackRow * tr = (trackRow *)malloc(sizeof(trackRow));
    tr->tracks = (char **)malloc(sizeof(char *) * count);
    tr->count = count;
    int i;
    for(i=0;i<count;i++){
        tr->tracks[i] = (char *)malloc(sizeof(char) * String_Max_Len);
        strcpy(tr->tracks[i],tracks[i]);
    }
    return tr;
}

bool cmpTracks(char **t1,int count1, char **t2, int count2){
    if(count1 != count2){
        return false;
    }

    int i,j,flag = 1;
    for(i=0;i<count1;i++){
        if(strcmp(t1[i],t2[i]) != 0)
            flag = 0;
    }
    return flag ? true : false;
}

bool isInSet(trackSet * set, trackRow * row){
    if(row == NULL){
        return false;
    }
    int i,flag=0;
    for(i=0;i<set->count;i++){
        if(cmpTracks(
                set->trackCollection[i]->tracks,
                set->trackCollection[i]->count,
                row->tracks,
                row->count
        )){
            flag = 1;
        }
    }
    return flag ? true : false;
}

void insertToSet(trackSet * set, trackRow * tR){
    if(tR == NULL){
        printf("insert fail, tR is NULL\n");
        return;
    }
    if(! isInSet(set,tR)){
        set->trackCollection = (trackRow **)realloc(set->trackCollection,sizeof(trackRow*) * (set->count + 1));    // 追加内存
        set->count ++;
        set->trackCollection[set->count - 1] = tR;
    }
}

trackSet * getA1FromT(database * db){
    trackSet * A1 = trackSetInit();

    int i,j;
    struct trackRow * pt;
    for(i=0;i<row_count;i++){
        for(j=0;j<db[i]->trajectoryCount;j++){
            pt = initOneRow(charToPChar(db[i]->trajectory[j]),1);
            insertToSet(A1,pt);
        }
    }
    return A1;
}

trackRow * joinTracks(trackRow * track1, trackRow * track2){
    int count1 = track1->count;
    int count2 = track2->count;
    int timediff = (track1->tracks[count1-1][1] - '0') - (track2->tracks[count2-1][1] - '0');   // 时间差

    if(count1 == 0 || count2 == 0 || (count1 != count2) || timediff == 0)
        return NULL;

    trackRow * result = (trackRow *)malloc(sizeof(trackRow *));
    result->tracks = (char **)malloc(sizeof(char *) * String_Max_Len * (track1->count));
    result->count = track1->count + 1;

    int i,j;

    // 如果可联结
    if(cmpTracks(track1->tracks,
                 track1->count - 1,
                 track2->tracks,
                 track2->count - 1
    )){
        // copy i - 1
        for(i=0;i< count1-1;i++){
//            memcpy(result->tracks[i],track1->tracks[i],sizeof());
            result->tracks[i] = track1->tracks[i];
        }
        // copy i i+1
        if(timediff < 0){
            result->tracks[count1 - 1] = track1->tracks[count1 - 1];
            result->tracks[count1] = track2->tracks[count1 - 1];
        }else{
            result->tracks[count1 - 1] = track2->tracks[count1 - 1];
            result->tracks[count1] = track1->tracks[count1 - 1];
        }

    }else{
        result = NULL;      // 注意不成功一定设置成NULL
    }

    return result;
}


void _printSetData(trackRow * row){
    int j;
    for(j=0;j<row->count;j++){
        printf("%s ",row->tracks[j]);
    }
}

void printSet(trackRow * row){
    int j;
    for(j=0;j<row->count;j++){
        printf("%s ",row->tracks[j]);
    }
}

void traverseSet(trackSet * set, void (*pfunc)(trackRow *)){
    int i;
    for(i=0;i<set->count;i++){
        pfunc(set->trackCollection[i]);
        printf("\n");
    }
}

void _str_test(){
    database * db = initDb();
    migrate(db,Db_Config_Path);
//    trackSet * set = getA1FromT(db);
    trackSet * set = trackSetInit();
    char * trs[2] = {"b2","d3"};
    char * trs2[2] = {"d3","c4"};
    trackRow * row1 = initOneRow(trs,2);
    trackRow * row2 = initOneRow(trs2,2);
    insertToSet(set,row1);
    insertToSet(set,row2);

    trackRow * row3 = joinTracks(row1,row2);
    if(row3 != NULL)
        insertToSet(set,row3);

    traverseSet(set,_printSetData);
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