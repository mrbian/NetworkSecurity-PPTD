//
// Created by bian on 2017/7/8.
//
#include "mpstd_print.h"

int mpstdBreakFunc(char * pzq, trackSet *Tc, database * Ts){
    system("cls");
    printf("�ڼ����pzq = %sʱ��Ts�Ľ��Ϊ��\n",pzq);
    sortDB(Ts);
    traverseDb(Ts,printRow);
    printf("\n");

    printf("��ʱΣ�չ켣����TcΪ��\n");
    traverseSet(Tc,printSet);
    printf("\n");

    printf("�س�������һ��ѭ�������������ַ��˳���ֱ�����SAGTD���\n");

    // ���stdin��ֹ��һ�α�����
    fflush(stdin);

    int result;
    result = getchar() == '\n' ? 1 : 0;
    return result;
}


int MPSTDChoice(){
    int choice;
    printf("���������1-3ѡ����Ҫ�鿴��MPSTD������\n");
    printf("1�����в鿴MPSTD�㷨���\n");
    printf("2�������𲽲鿴MPSTD�㷨���\n");
    printf("3���˳�MPSTD�㷨\n");
    printf("���������1-3��");
    while( scanf("%d",&choice) == 0 || choice < 0 || choice > 3){
        printf("���벻�Ϸ���������1-3֮�������");
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
                printf("MPSTD���к�Tg�����\n");
                sortDB(Tg);
                traverseDb(Tg,printRow);
                break;

            case 2:
                Tg = mpstd(originDB,root,Ts,A,PbThreshold,maxDepth,1,mpstdBreakFunc);
                printf("MPSTD���к�Tg�����\n");
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