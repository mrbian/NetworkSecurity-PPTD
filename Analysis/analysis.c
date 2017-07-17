//
// Created by bian on 2017/7/16.
//
#include <time.h>
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

void coverDatabaseToFile(database *db, char * destFilePath){
    FILE *fp;
    if((fp = fopen(destFilePath,"w+")) == NULL){
        printf("open file fail\n");
        exit(-1);
    };
    fclose(fp);

    appendDatabaseToFile(db,destFilePath);
}

void generateBigDatabase(char * srcFilePath, char * destFilePath, int loopTimes){
    database * cache = initDb();
    migrate(cache,srcFilePath);
//    traverseDb(cache,printRow);

    FILE *fp;
    if((fp = fopen(destFilePath,"w+")) == NULL){
        printf("open file fail\n");
        exit(-1);
    };
    fclose(fp);

    int i,j,len;
    len = getLengthOfDB(cache);
    for(i=0;i<loopTimes;i++){
        appendDatabaseToFile(cache,destFilePath);
        for(j=0;j<len;j++){
            cache[j]->id += len;
        }
    }
    printf("generate data file over\n");
}

int SAGTDBreakFunc(database * Bj, database *Cj,  database * T, float PbThreshold, int maxDepth, trackRow * attack_row);

int MPSTDBreakFunc(char * a, trackSet *b, database *c){};

void sagtdProcess(treeNode * root, database * originDB,int maxDepth,float PbThreshold){
    double  start, finish;
    start = clock();//ȡ��ʼʱ��
    printf("sagtd processing!\n");

    database * db = initDb();
    migrate(db,BIG_DB_FILE_PATH);

    db = SAGTD(originDB,db,root,maxDepth,PbThreshold,maxDepth,0,SAGTDBreakFunc);
    sortDB(db);

    finish = clock();//ȡ����ʱ��
    printf( "Process 1400 line data, sagtd use %f seconds\n",(finish - start) / CLOCKS_PER_SEC);//����Ϊ��λ��ʾ֮

    coverDatabaseToFile(db,SAGTD_DB_FILE_PATH);
}

void mpstdProcess(treeNode * root, database * originDB, int maxDepth,float PbThreshold){
    double  start, finish;
    start = clock();//ȡ��ʼʱ��
    trackSet *A = str_main(originDB,maxBackgroundSetLength);
    printf("mpstd processing!\n");

    database * mdb = initDb();
    migrate(mdb,SAGTD_DB_FILE_PATH);

    mdb = mpstd(originDB,root,mdb,A,PbThreshold,maxDepth,0,MPSTDBreakFunc);
    sortDB(mdb);
    coverDatabaseToFile(mdb,MPSTD_DB_FILE_PATH);

    finish = clock();//ȡ����ʱ��
    printf( "Process 1400 line data, mpstd use %f seconds\n",(finish - start) / CLOCKS_PER_SEC);//����Ϊ��λ��ʾ֮

}

void analysis_main(){
//    generateBigDatabase(DB_FILE_PATH_3,BIG_DB_FILE_PATH,200);
//
    double  start, finish;
    start = clock();//ȡ��ʼʱ��
    printf("the sagtd and mpstd processing!\n");

    database * originDB = initDb();
    migrate(originDB,BIG_DB_FILE_PATH);     // originDB
    treeNode * root = migrateTree(CONFIG_PATH);
    int maxDepth = 2;
    float PbThreshold = 0.5;

    sagtdProcess(root,originDB,maxDepth,PbThreshold);
    // todo 1K���ݼ���ʱ����
//    mpstdProcess(root,originDB,maxDepth,PbThreshold);

    finish = clock();//ȡ����ʱ��
    printf( "Process 1400 line data, sagtd and mpstd use %f seconds\n",(finish - start) / CLOCKS_PER_SEC);//����Ϊ��λ��ʾ֮

    system("pause");
}