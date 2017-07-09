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
    printf("5、对当前数据库实施MPSTD算法，设置最大泛化深度和泄露概率阈值，查看过程（自动运行一次SAGTD）\n");
    printf("6、输出原始数据库\n");
    printf("7、重置数据库\n");
    printf("8、退出程序\n");
    printf("请输入1-8选择相应的选项：");
    scanf("%d",&choice);
    if(choice > 8 || choice < 1){
        printf("输入不合法\n");
        return -1;
    }
    return choice;
}

// 3、输入攻击序列计算泄露概率函数
void caculateFunc(database * originDB,treeNode * root, database *db){
    while(1){
        int row_id, t_count = 1, i = 0;
        char ** track;
        printf("当前数据库为：\n");
        traverseDb(db,printRow);

        printf("请输入攻击序列个数：");
        scanf("%d", &t_count);
        printf("请输入攻击序列：");
        track = (char **)malloc(sizeof(char *) * t_count);
        while(i < t_count){
            track[i] = (char *)malloc(sizeof(char) * 3);
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
        printf("回车进入下一次计算，输入任意字符退出\n");

        // 清空stdin
        fflush(stdin);

        int result;
        result = getchar() == '\n' ? 1 : 0;
        if(!result){
            return;
        }else{
            system("cls");
        }
    }
}

void main_thread(database * originDB,treeNode * root,database * db){
    int maxDepth;
    float PbThreshold;
    printf("请输入最大泛化深度:");
    while(scanf("%d",&maxDepth) == 0 && maxDepth < 0 || maxDepth > treeHeight){
        printf("输入不合法，请输入%d-%d之间的数\n",0,treeHeight);
    }

    printf("请设置泄露概率阈值：");
    scanf("%f",&PbThreshold);
    while(PbThreshold < 0 || PbThreshold > 1){
        printf("输入不合法，泄露概率在0-1之间\n");
        scanf("%f",&PbThreshold);
    }

    int choice;
    trackSet * A;
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
                system("cls");
                caculateFunc(originDB,root,db);
                break;

            case 4:
                system("cls");
                db = SAGTDFunc(originDB,root,db, maxDepth, PbThreshold);
                break;

            case 5:
                system("cls");
                A = str_main(db,maxDepth);
                db = SAGTD(originDB,db,root,maxDepth,PbThreshold,maxDepth,0,SAGTDNonBreakFunc);
                db = MPSTDFunc(originDB,root,db,A,maxDepth,PbThreshold);
                break;

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
