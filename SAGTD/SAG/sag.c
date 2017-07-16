//
// Created by bian on 2017/7/6.
//
#include <mem.h>
#include "sag.h"

bool isInDb(database * db, row * row){
    if(row == NULL){
        printf("row is NULL, check it!\n");
        return false;
    }
    int i,flag = 0;
    for(i=0;i<row_count;i++){
        if(db[i] == NULL)
            continue;

        if(db[i]->id == row->id){
            flag = 1;
            break;
        }
    }

    return flag ? true : false;
}

database * DBSub(database * minuend, database * subtracted){
    database * result = initDb();
    int i;
    for(i=0;i<row_count;i++){

        if(minuend[i] == NULL)
            continue;

        if(! isInDb(subtracted,minuend[i])){    // 不在则插入到结果内
            insertRow(result,minuend[i]->id,minuend[i]->p_level,minuend[i]->trajectory,minuend[i]->trajectoryCount,minuend[i]->disease);
        }

    }

    return result;
}

database * DBUnion(database * db1, database *db2){
    database * result = initDb();
    int i;
    for(i=0;i<row_count;i++){
        if(db1[i] != NULL && ! isInDb(result,db1[i])){      // 非空且不在结果内
            insertRow(result,db1[i]->id,db1[i]->p_level,db1[i]->trajectory,db1[i]->trajectoryCount,db1[i]->disease);
        }

        if(db2[i] != NULL && ! isInDb(result,db2[i])){
            insertRow(result,db2[i]->id,db2[i]->p_level,db2[i]->trajectory,db2[i]->trajectoryCount,db2[i]->disease);
        }
    }

    return result;
}

void changeDbRowSensitiveValue(database *db, int rowId, char * disease){
    row * row = getRowById(db,rowId);
    if(row == NULL){
        printf("Db is bad oops\n");
        return;
    }
    strcpy(row->disease,disease);
}

database * sag(database * originDB, database * db, treeNode * root, trackRow * background, database * Cj, int maxDepth, float PbThreshold){
//    traverseDb(Cj,printRow);
    database * Sj = initDb();
    database * Dj;
    database * db_free_temp;        // 将不用空间free掉
    int i,j;
    float pb = 0;
    treeNode * twinNode, * guardingNode;
    // 2 - 11
    for(i=0;i<row_count;i++){
        if(Cj[i] == NULL)
            continue;
        // 3 - 4
        twinNode = getTwinNodeByRow(root,Cj[i]);
        guardingNode = getGuardingNodeByRow(originDB, root,Cj[i]->id);
        if(twinNode == guardingNode || nodeAisCoveredByNodeB(root,twinNode,guardingNode)){

            if(guardingNode->parent != NULL){
                strcpy(Cj[i]->disease,guardingNode->parent->text);      // 赋值守护节点的父节点属性
                changeDbRowSensitiveValue(db,Cj[i]->id,guardingNode->parent->text);     // 修改全局Db，Cj和Db不是同一内存空间
            }
            // 5
            pb = caculateBreachProbability(originDB, db,root,Cj[i]->id,background->tracks,background->count);
            if( pb <= PbThreshold){
                // 6
                Dj = initDb();
                for(j=0;j<row_count;j++){
                    if(Cj[j] == NULL)
                        continue;

                    if(getGuardingNodeByRow(originDB, root,Cj[j]->id) == getGuardingNodeByRow(originDB, root,Cj[i]->id)){
                        insertRow(Dj,Cj[j]->id,Cj[j]->p_level,Cj[j]->trajectory,Cj[j]->trajectoryCount,Cj[j]->disease);
                    }
                }

                // 7 - 8
                db_free_temp = Cj;
                Cj = DBSub(Cj,Dj);
                freeDb(db_free_temp);

                db_free_temp = Sj;
                Sj = DBUnion(Sj,Dj);
                freeDb(db_free_temp);

                freeDb(Dj);
            }
        }
    }

//    traverseDb(Sj,printRow);
//    traverseDb(Cj,printRow);

    // 12 - 25
    database * temp;
    while(getLengthOfDB(Cj) !=0 ){
        for(i=0;i<row_count;i++){
            if(Cj[i] == NULL)
                continue;

            // 14 - 16
            if(getNodeHeight(root,getTwinNodeByRow(root, Cj[i])) - getNodeHeight(root,getGuardingNodeByRow(originDB, root,Cj[i]->id)) >= maxDepth
               || getNodeHeight(root,getTwinNodeByRow(root, Cj[i])) == treeHeight) {

                temp = initDb();
                insertRow(temp, Cj[i]->id, Cj[i]->p_level, Cj[i]->trajectory, Cj[i]->trajectoryCount, Cj[i]->disease);

                db_free_temp = Cj;
                Cj = DBSub(Cj, temp);
                freeDb(db_free_temp);

                db_free_temp = Sj;
                Sj = DBUnion(Sj, temp);
                freeDb(db_free_temp);

                freeDb(temp);

            }
            // 17 -20
            else if( caculateBreachProbability(originDB, db,root,Cj[i]->id,background->tracks,background->count) <= PbThreshold){
                Dj = initDb();
                for(j=0;j<row_count;j++){
                    if(Cj[j] == NULL)
                        continue;

                    if(getGuardingNodeByRow(originDB, root,Cj[j]->id) == getGuardingNodeByRow(originDB, root,Cj[i]->id)){
                        insertRow(Dj,Cj[j]->id,Cj[j]->p_level,Cj[j]->trajectory,Cj[j]->trajectoryCount,Cj[j]->disease);
                    }
                }

                db_free_temp = Cj;
                Cj = DBSub(Cj,Dj);
                freeDb(db_free_temp);

                db_free_temp = Sj;
                Sj = DBUnion(Sj,Dj);
                freeDb(db_free_temp);

                freeDb(Dj);
            }
            else {
                // 22
                treeNode * t_temp = getTwinNodeByRow(root,Cj[i]);
                if(t_temp->parent != NULL){
                    strcpy(Cj[i]->disease, t_temp->parent->text);
                    changeDbRowSensitiveValue(db, Cj[i]->id, t_temp->parent->text);     // 修改全局Db，Cj和Db不是同一内存空间
                }
            }

        }
    }

    return Sj;
}
