//
// Created by bian on 2017/7/16.
//
#include "analysis.h"

char* join(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    if (result == NULL) exit (1);

    strcpy(result, s1);
    strcat(result, s2);

    return result;
}

void appendDatabaseToFile(database * db, char * destFilePath){
    FILE *fp;
    int i,j,count;
    char * trajectory = NULL;
    count = getLengthOfDB(db);
    if((fp = fopen(destFilePath,"a")) == NULL){
        printf("open file fail\n");
        exit(-1);
    };

    for(i=0;i<row_count;i++){
        if(db[i] == NULL)
            continue;

        free(trajectory);
        trajectory = NULL;

        trajectory = malloc(sizeof(char) * trajectory_item_num * movePointLen);

        trajectory = join("",db[i]->trajectory[0]);
        for(j=1;j<db[i]->trajectoryCount;j++){
            trajectory = join(trajectory,",");
            trajectory = join(trajectory,db[i]->trajectory[j]);
        }
        fprintf(fp,"%d,%d,%s %s\n",db[i]->id,db[i]->p_level,trajectory,db[i]->disease);
    }

    fclose(fp);
}

void generateBigDatabase(char * srcFilePath, char * destFilePath, int loopTimes){
    database * cache = initDb();
    migrate(cache,srcFilePath);
//    traverseDb(cache,printRow);

    int i,j,len;
    len = getLengthOfDB(cache);
    for(i=0;i<loopTimes;i++){
        appendDatabaseToFile(cache,destFilePath);
        for(j=0;j<len;j++){
            cache[j]->id += len;
        }
    }
    printf("generate over");
}

int SAGTDBreakFunc(database * Bj, database *Cj,  database * T, float PbThreshold, int maxDepth, trackRow * attack_row);

void analysis_main(){
//    generateBigDatabase(DB_FILE_PATH_3,BIG_DB_FILE_PATH,200);

    database * originDB = initDb();
    migrate(originDB,BIG_DB_FILE_PATH);     // originDB

    // DB
    database * db = initDb();
    migrate(db,BIG_DB_FILE_PATH);

    // tree
    treeNode * root = migrateTree(CONFIG_PATH);

    int maxDepth = 2;
    float PbThreshold = 0.5;

    db = SAGTD(originDB,db,root,maxDepth,PbThreshold,maxDepth,0,SAGTDBreakFunc);
    sortDB(db);
    traverseDb(db,printRow);
}