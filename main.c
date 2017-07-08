#include <stdio.h>
#include "LinkedList/LinkedList.h"
#include "Tree/tree.h"
#include "Database/database.h"
#include "SAGTD/common/common.h"
#include "SAGTD/STR/str.h"
#include "SAGTD/SAGTD.h"
#include "MPSTD/MPSTD.h"
#include "sagtd_print.h"
#include "mpstd_print.h"

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
    printf("8、退出程序\n");
    printf("请输入1-7选择相应的选项：");
    scanf("%d",&choice);
    if(choice > 8 || choice < 1){
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

            case 8:
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

    // 直接结果
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
