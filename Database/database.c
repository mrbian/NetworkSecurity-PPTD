//
// Created by bian on 2017/7/4.
//
#include <malloc.h>
#include <mem.h>
#include "database.h"

// todo 防重复
bool insertRow(database * db, int id,int p_level, char** trajectory,int count, char disease[disease_len]){
    int i;
    int curPos = 0;
    for(curPos = 0;curPos < row_count;curPos ++){
        if(db[curPos] == NULL)
            break;
    }
    db[curPos] = (row *)malloc(sizeof(row));        // 这里是sizeof(row)而不是sizeof(row*)!!!
    db[curPos]->id = id;
    db[curPos]->p_level = p_level;
    db[curPos]->trajectoryCount = 0;
    strcpy(db[curPos]->disease,disease);
    db[curPos]->trajectory = (char **)malloc(sizeof(char *) * trajectory_item_num);

    // 行内存不连续
    //    memcpy(db[curPos]->trajectory,trajectory,sizeof(char) * trajectory_item_num * 100);  // 注意&t_num + 1
    for(i=0;i<count;i++){
        db[curPos]->trajectory[i] = trajectory[i];
        db[curPos]->trajectoryCount ++;
    }
    return true;
}

database * initDb(){
    database* db = (database *)malloc(sizeof(database) * row_count);
    int i;
    for(i=0;i<row_count;i++){
        db[i] = NULL;
    }
    return db;
}

void migrate(database * db,char * filePath){
    int i = 0;
    int id;
    int p_level;
    char * trajectory_str = (char *)malloc(sizeof(char) * 100);
    char * disease_str = (char *)malloc(sizeof(char) * 100);
    char ** trajectories = (char**)malloc(sizeof(char*) * trajectory_item_num);
    char * result;

    FILE * fp;
    if((fp = fopen(filePath,"r")) == NULL){
        printf("open file fail\n");
        exit(-1);
    };

    while( fscanf(fp,"%d,%d,%s %[^\f\n\t\v\r]",&id,&p_level,trajectory_str,disease_str) != EOF ){
        i = 0;
        result = strtok(trajectory_str,",");        // 改变了t_str，不用strtok可以挨个字符处理，压栈出栈
        while(result != NULL){
            trajectories[i] = (char *)malloc(sizeof(char) * 100);
            strcpy(trajectories[i],result);
            i++;
            result = strtok(NULL, ",");
        }

        insertRow(db,id,p_level,trajectories,i,disease_str);

        // 所有都要重新分配
        trajectory_str = (char *)malloc(sizeof(char) * 100);
        disease_str = (char *)malloc(sizeof(char) * 100);
        trajectories = (char**)malloc(sizeof(char*) * trajectory_item_num);
    }
    fclose(fp);
}

void printRow(row * row){
    printf("%-5d%-5d%-10s",row->id,row->p_level,row->disease);
    int i =0;
    printf("  <");
    for(i=0;i<row->trajectoryCount;i++){
        printf("%s,",row->trajectory[i]);
    }
    printf(">\n");
}

void traverseDb(database * db, void (*pfunc)(row *)){
    int i = 0;
    for(i=0;i<row_count;i++){
        if(db[i] != NULL){
            pfunc(db[i]);
        }
    }
}

row* getRowById(database  * db, int id){
    int i = 0;
    for(i=0;i<row_count;i++){
        if(db[i] != NULL && db[i]->id == id){
            return db[i];
        }
    }
    return NULL;
}

database * getRowsByTrajectory(database * db, char * tr){
    int i,j;
    int idx = 0;
    database * rowCollection = (database *)malloc(sizeof(row *) * row_count);
    for(i=0;i<row_count;i++){
        rowCollection[i] = NULL;
    }

    for(i=0;i<row_count;i++){
        if(db[i] == NULL)
            continue;
        for(j=0;j<db[i]->trajectoryCount;j++){
            if(strcmp(db[i]->trajectory[j],tr) == 0){
                rowCollection[idx] = db[i];
                idx ++;
                break;
            }
        }
    }

    return rowCollection;
}

void sortDB(database * db){
    row * r_temp;
    int i,j;
    for(i=0;i<row_count - 1;i++){
        if(db[i] == NULL)
            continue;

        for(j=0;j<row_count - 1 - i;j++){
            if((db[j] == NULL) || (db[j+1] == NULL))
                continue;

            if(db[j]->id > db[j+1]->id){
                r_temp = db[j];
                db[j] = db[j+1];
                db[j+1] = r_temp;
            }
        }
    }
}

void _db_main(){
    database * db = initDb();   // 初始化
    migrate(db,DB_FILE_PATH_3);    // 赋Example3值

    traverseDb(db,printRow);      // 打印数据库
}