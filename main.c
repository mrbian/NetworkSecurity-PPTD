#include <stdio.h>
#include "LinkedList/LinkedList.h"
#include "BinaryTreeNode/BinaryTreeNode.h"
#include "Queue/queue.h"
#include "Tree/tree.h"
#include "Database/database.h"
#include "SAGTD/common/common.h"
#include "SAGTD/STR/str.h"
#include "SAGTD/SAGTD.h"
#include "MPSTD/MPSTD.h"

//#define δ 2
//#define σ 0.5

// 总循环打印函数
int inputChoice(){
    int choice;
    printf("--------------------------------------PPTD--------------------------------------\n");
    printf("1、输出当前数据库\n");
    printf("2、广度优先遍历输出敏感属性树\n");
    printf("3、输入攻击序列计算当前数据库某行泄露概率\n");
    printf("4、对当前数据库实施SAGTD算法，设置最大泛化深度和泄露概率阈值，查看过程\n");
    printf("5、对当前数据库实施MPSTD算法，设置最大泛化深度和泄露概率阈值，查看过程\n");
    printf("6、输出原始数据库\n");
    printf("7、重置数据库\n");
    printf("请输入1-7选择相应的选项：");
    scanf("%d",&choice);
    if(choice > 7 || choice < 1){
        printf("输入不合法\n");
        return -1;
    }
    return choice;
}

// 3、输入攻击序列计算泄露概率函数
void caculateFunc(database * originDB,treeNode * root, database *db){
    int row_id, t_count, i = 0;
    char ** track;
    printf("当前数据库为：\n");
    traverseDb(db,printRow);

    printf("请输入攻击序列个数\n");
    scanf("%d", &t_count);
    printf("请输入攻击序列\n");
    track = (char **)malloc(sizeof(char *) * t_count);
    while(i < t_count){
        scanf("%s",track[i]);
        i++;
    }
    trackRow * row = initOneRow(track,t_count);

    printf("请输入待计算的行的id：");
    scanf("%d",&row_id);
    while(row_id > 7 || row_id < 1){
        printf("输入不合法，请重新输入；\n");
        printf("请输入行id：");
        scanf("%d",&row_id);
    }

    printf("本行的泄露概率是: %-5.2f\n", caculateBreachProbability(originDB,db,root,row_id,row->tracks,row->count));
}

// SAGTD逐步打印函数
int SAGTDBreakFunc(database * Bj, database *Cj,  database * T, float PbThreshold, int maxDepth, trackRow * attack_row){
    printf("当前最大泛化深度是%5d，泄露概率阈值是%5.2f\n",maxDepth,PbThreshold);
    printf("当前攻击序列为\n");
    _printSetData(attack_row);
    printf("Bj的结果是\n");
    traverseDb(Bj,printRow);
    printf("Cj的结果是\n");
    traverseDb(Cj,printRow);
    printf("SAG算法后结果T是\n");
    traverseDb(T,printRow);
    printf("回车进入下一次循环，输入任意字符停止逐步输出，直接输出SAGTD结果\n");
    char * input = (char*)malloc(sizeof(char) * 100);
    int result;
    result = gets(input)[0] == '\0' ? 1 : 0;
    free(input);
    input = NULL;
    return result;
}

// SAGTD不逐步打印函数
int SAGTDNonBreakFunc(database * Bj, database *Cj,  database * T, float PbThreshold, int maxDepth, trackRow * attack_row){
    return 0;
}

// 4、对当前数据库实施SAGTD算法，设置最大泛化深度和泄露概率阈值，查看过程
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

// SAGTD算法函数
void SAGTDFunc(database * originDB,treeNode * root,database * db){
    int maxDepth;
    float Pb;
    printf("请输入最大泛化深度:");
    scanf("%d",&maxDepth);
    while(maxDepth < 0 || maxDepth > treeHeight){
        printf("输入不合法，请输入%d-%d之间的数\n",0,treeHeight);
        scanf("%d",&maxDepth);
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
                traverseDb(Ts,printRow);
                break;

            case 5:
                return;

            default:
                continue;
        }

        system("pause");

    }
}

void main_thread(database * originDB,treeNode * root,database * db){
    int choice;
    while(1){
        choice = inputChoice();

        switch(choice){
            case 1:
                sortDB(db);
                traverseDb(db,printRow);
                break;

            case 2:
                traverseTree(root,_printText);
                break;

            case 3:
                caculateFunc(originDB,root,db);
                break;

            case 4:
                SAGTDFunc(originDB,root,db);
                break;

            case 5:
                return;

            case 6:
                printf("原始数据库是\n");
                traverseDb(originDB,printRow);
                break;

            case 7:
                // todo : 原内存未释放
                db = initDb();
                migrate(db,DB_FILE_PATH_3);
                break;
        }

        system("pause");
    }
}

int main()
{
//    _main_test();
    // origin DB
    database * originDB = initDb();
    migrate(originDB,DB_FILE_PATH_3);     // originDB

    // DB
    database * db = initDb();
    migrate(db,DB_FILE_PATH_3);

    // tree
    treeNode * root = migrateTree(CONFIG_PATH);

    main_thread(originDB,root,db);

//    int maxDepth = 2;
//    float Pb = 0.5;
//    // STR
//    trackSet * A = str_main(originDB,maxDepth);
//
//    // SAGTD
//    database * Ts = SAGTD(originDB,root, maxDepth ,Pb, maxDepth);
//    sortDB(Ts);
//    printf("After SAGTD the result is \n");
//    traverseDb(Ts,printRow);
//    printf("\n");
//
//
//    // MPSTD
//    database * Tg = mpstd(originDB,root,Ts,A,Pb, maxDepth);
//    sortDB(Tg);
//    printf("After MPSTD the result is \n");
//    traverseDb(Tg,printRow);
//    printf("\n");

    return 0;
}
