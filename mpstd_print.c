//
// Created by bian on 2017/7/8.
//
#include "mpstd_print.h"

int mpstdBreakFunc(char * pzq, trackSet *Tc, database * Ts){
    system("cls");
    printf("在计算出pzq = %s时，Ts的结果为：\n",pzq);
    sortDB(Ts);
    traverseDb(Ts,printRow);
    printf("\n");

    printf("此时危险轨迹集合Tc为：\n");
    traverseSet(Tc,printSet);
    printf("\n");

    printf("回车进入下一次循环，输入任意字符退出，直接输出SAGTD结果\n");

    // 清空stdin防止第一次被跳过
    fflush(stdin);

    int result;
    result = getchar() == '\n' ? 1 : 0;
    return result;
}


int MPSTDChoice(){
    int choice;
    printf("请输入序号1-3选择想要查看的MPSTD操作：\n");
    printf("1、运行查看MPSTD算法结果\n");
    printf("2、运行逐步查看MPSTD算法结果\n");
    printf("3、退出MPSTD算法\n");
    printf("请输入序号1-3：");
    while( scanf("%d",&choice) == 0 || choice < 0 || choice > 3){
        printf("输入不合法，请输入1-3之间的数：");
    }
    return choice;
}

database * MPSTDFunc(database * originDB,treeNode * root,database * Ts, trackSet *A, int maxDepth, float PbThreshold){
    int choice;
    database *Tg = Ts;

    while(1){
        choice = MPSTDChoice();

        switch(choice){
            case 1 :
                Tg = mpstd(originDB,root,Ts,A,PbThreshold,maxDepth,0,mpstdBreakFunc);
                printf("MPSTD运行后Tg结果是\n");
                sortDB(Tg);
                traverseDb(Tg,printRow);
                break;

            case 2:
                Tg = mpstd(originDB,root,Ts,A,PbThreshold,maxDepth,1,mpstdBreakFunc);
                printf("MPSTD运行后Tg结果是\n");
                sortDB(Tg);
                traverseDb(Tg,printRow);
                break;

            case 3:
                return Tg;

            default:
                continue;
        }

        system("pause");
        system("cls");
    }
}