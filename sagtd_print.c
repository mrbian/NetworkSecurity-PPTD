//
// Created by bian on 2017/7/8.
//

#include "sagtd_print.h"


int SAGTDBreakFunc(database * Bj, database *Cj,  database * T, float PbThreshold, int maxDepth, trackRow * attack_row){
    system("cls");
    printf("当前最大泛化深度是%5d，泄露概率阈值是%5.2f\n",maxDepth,PbThreshold);
    printf("当前攻击序列为：");
    _printSetData(attack_row);

    printf("Bj的结果是\n");
    sortDB(Bj);
    traverseDb(Bj,printRow);
    printf("\n");

    printf("Cj的结果是\n");
    sortDB(Cj);
    traverseDb(Cj,printRow);
    printf("\n");

    printf("SAG算法后结果T是\n");
    sortDB(T);
    traverseDb(T,printRow);
    printf("\n");

    printf("回车进入下一次循环，输入任意字符退出，直接输出SAGTD结果\n");
    char * input = (char*)malloc(sizeof(char) * 100);
    int result;
    result = gets(input)[0] == '\0' ? 1 : 0;
    free(input);
    input = NULL;
    return result;
}

int SAGTDNonBreakFunc(database * Bj, database *Cj,  database * T, float PbThreshold, int maxDepth, trackRow * attack_row){
    return 0;
}

int SAGTDChoice(){
    int choice;
    printf("请输入序号1-4选择想要查看的SAGTD操作：\n");
    printf("1、查看STR算法结果\n");
    printf("2、逐步查看SAGTD结果\n");
    printf("3、重置数据库\n");
    printf("4、查看SAGTD结果\n");
    printf("5、退出SAGTD算法\n");
    printf("请输入序号1-5：");
    while( scanf("%d",&choice) == 0 || choice < 0 || choice > 5){
        printf("输入不合法，请输入1-5之间的数：");
    }
    return choice;
}

void SAGTDFunc(database * originDB,treeNode * root,database * db){
    int maxDepth;
    float Pb;
    printf("请输入最大泛化深度:");
    while(scanf("%d",&maxDepth) == 0 && maxDepth < 0 || maxDepth > treeHeight){
        printf("输入不合法，请输入%d-%d之间的数\n",0,treeHeight);
    }

    printf("请设置泄露概率阈值：");
    scanf("%f",&Pb);
    while(Pb < 0 || Pb > 1){
        printf("输入不合法，泄露概率在0-1之间\n");
        scanf("%f",&Pb);
    }

    int choice;
    trackSet *A;
    database *Ts;
    while(1){
        choice = SAGTDChoice();

        switch(choice){
            case 1:
                A = str_main(db,maxDepth);
                traverseSet(A,printSet);
                printf("攻击序列的个数是：%d\n", A->count);
                break;

            case 2:
                Ts = SAGTD(originDB,db,root,maxDepth,Pb,maxDepth,1,SAGTDBreakFunc);
                printf("SAGTD结果为：\n");
                sortDB(Ts);
                traverseDb(Ts,printRow);
                break;

            case 3:
                // todo 原内存未释放
                db = initDb();
                migrate(db,DB_FILE_PATH_3);
                Ts = db;
                printf("重置结果为\n");
                traverseDb(db,printRow);
                break;

            case 4:
                Ts = SAGTD(originDB,db,root,maxDepth,Pb,maxDepth,0,SAGTDNonBreakFunc);
                printf("SAGTD结果为：\n");
                sortDB(Ts);
                traverseDb(Ts,printRow);
                break;

            case 5:
                return;

            default:
                system("pause");
                system("cls");
                continue;
        }

        system("pause");
        system("cls");
    }
}