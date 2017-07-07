//
// Created by bian on 2017/7/5.
//
#include "common.h"

// 根据ri的guard node和rk的twin node计算概率
float _getProbabilityByNode(treeNode * root, treeNode * guardingNode, treeNode * twinNode){
    float result = 0;
    if(nodeAisCoveredByNodeB(root,twinNode,guardingNode)|| guardingNode == twinNode){

        return 1;

    }else if(nodeAisCoveredByNodeB(root,guardingNode,twinNode) ){

        int i,j,flag;   // 集合A中元素是否匹配到集合B的元素
        int mem = 0;    // 分子
        int den = getSubsetsLengthOfNode(twinNode);     // 分母
        treeNode **guardingNodeSets = getSubsetsOfNode(guardingNode);
        treeNode **twinNodeSets = getSubsetsOfNode(twinNode);

        for (i = 0; i < getSubsetsLengthOfNode(twinNode); i++) {
            flag = 0;       // 默认未匹配到
            for (j = 0; j < getSubsetsLengthOfNode(guardingNode); j++) {
                if (twinNodeSets[i] == guardingNodeSets[j])
                    flag = 1;
            }
            if (flag)
                mem++;
        }

        result = (float) mem / (float) den;
        return ((float)((int)(result * 100))) / 100;
    }else{
        return 0;
    }

}

float caculateBreachProbability(database * originDb, database * db,treeNode * root, int rowId, char ** background, int backgroundCount){
    row * row = getRowById(db,rowId);           // 待求值的行
    if(row->p_level == -1){     // 如果是No Privacy
        return 0;
    }
    database * rowsMatched = matchRowByTrajectory(db,background,backgroundCount);   // 攻击者匹配到的行
//    printf("matched %d\n",getLengthOfDB(rowsMatched));
    treeNode * guardingNode = getGuardingNodeByRow(originDb, root, rowId);   // ri的guard node
    treeNode * twinNode;        // rk 的twin node

    int i,count = 0;    // count 记录Tk行数
    float result = 0;
    for(i=0;i<row_count;i++){
        if(rowsMatched[i] != NULL){
            twinNode = getTwinNodeByRow(root,rowsMatched[i]);   // rk 的twin node
//            printf("ri is r%d, rk is r%d,the p is %.2f\n",rowId,rowsMatched[i]->id,_getProbabilityByNode(root,guardingNode,twinNode));
            result += _getProbabilityByNode(root,guardingNode,twinNode);
            count ++;
        }
    }
    result = result  / (float)count;
    result = ((float)((int)(result * 100))) / 100;
    return result;
}

treeNode * getGuardingNodeByRow(database * originDb, treeNode * root, int rowId){
    row * row = getRowById(originDb,rowId);
    int p_level = row->p_level;
    treeNode* pt = getNodeByText(root, row->disease);
    while(p_level > 0 && pt->parent != NULL){
        pt = pt->parent;
        p_level --;
    }
    return pt;
}

treeNode * getTwinNodeByRow(treeNode * root, row * row){
    return getNodeByText(root,row->disease);
}

database * matchRowByTrajectory(database * db, char ** trCollection, int count){
    int i = 0;
    database * rowCollection = db;

    while(count --){
        rowCollection = getRowsByTrajectory(rowCollection,trCollection[i]);
        i++;
    }
    return rowCollection;
}

database * getIntersectionOfRows(database * db1, database * db2){
    database * result = initDb();
    int i,j;
    for(i=0;i<row_count;i++){
        if(db1[i] == NULL){
            continue;
        }
        for(j=0;j<row_count;j++){
            if(db2[j] == NULL){
                continue;
            }
            if(db1[i]->id == db2[j]->id){
                insertRow(result,
                          db1[i]->id,
                          db1[i]->p_level,
                          db1[i]->trajectory,
                          db1[i]->trajectoryCount,
                          db1[i]->disease
                );
            }
        }
    }
    return result;
}

int getLenOfintersectionOfRows(database * db1,database * db2){
    if(db1 == NULL || db2 == NULL){
        return 0;
    }
    database * result = getIntersectionOfRows(db1,db2);
    int i,count=0;
    for(i=0;i<row_count;i++){
        if(result[i] != NULL){
            count ++;
        }
    }
    return count;
}

int getLengthOfDB(database * db){
    int i,count = 0;
    for(i=0;i<row_count;i++){
        if(db[i] != NULL)
            count++;
    }
    return count;
}

char ** charToPChar(char * str){
    char ** temp = (char **)malloc(sizeof(char *));
    temp[0] = str;
    return temp;
}

void _common_main(database * originDB){
    database * db = initDb();   // 初始化
    migrate(db,DB_FILE_PATH_3);    // 赋值

    database * db2 = initDb();
    migrate(db2,DB_FILE_PATH_4);

    treeNode * root = migrateTree(CONFIG_PATH);

//    treeNode * A = getNodeByText(root,"Infectious Disease");
//    treeNode * B = getNodeByText(root,"HIV");
//    printf("%d",nodeAisCoveredByNodeB(root,A,B));

    char *background[1] = {"a7"};
    int r = 2;
    float result = caculateBreachProbability(originDB, db,root,r,background, sizeof(background) / sizeof(background[0]));
    printf("Before Pb'sresult is %.2f\n",result);

    float result2 = caculateBreachProbability(originDB, db2,root,r,background, sizeof(background) / sizeof(background[0]));
    printf("After Pb'sresult is %.2f\n",result2);

//    char* background[2] = {"b2","e8"};
//    database * rowCollection = matchRowByTrajectory(db,background,sizeof(background) / (sizeof(background[0])));
//    int i;
//    for(i=0;i<row_count;i++){
//        if(rowCollection[i] != NULL){
//            printf("the matched row id is %d\n",rowCollection[i]->id);
//        }
//    }
}