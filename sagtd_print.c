//
// Created by bian on 2017/7/8.
//

#include "sagtd_print.h"


int SAGTDBreakFunc(database * Bj, database *Cj,  database * T, float PbThreshold, int maxDepth, trackRow * attack_row){
    system("cls");
    printf("��ǰ��󷺻������%5d��й¶������ֵ��%5.2f\n",maxDepth,PbThreshold);
    printf("��ǰ��������Ϊ��");
    _printSetData(attack_row);

    printf("Bj�Ľ����\n");
    sortDB(Bj);
    traverseDb(Bj,printRow);
    printf("\n");

    printf("Cj�Ľ����\n");
    sortDB(Cj);
    traverseDb(Cj,printRow);
    printf("\n");

    printf("SAG�㷨����T��\n");
    sortDB(T);
    traverseDb(T,printRow);
    printf("\n");

    printf("�س�������һ��ѭ�������������ַ��˳���ֱ�����SAGTD���\n");
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
    printf("���������1-4ѡ����Ҫ�鿴��SAGTD������\n");
    printf("1���鿴STR�㷨���\n");
    printf("2���𲽲鿴SAGTD���\n");
    printf("3���������ݿ�\n");
    printf("4���鿴SAGTD���\n");
    printf("5���˳�SAGTD�㷨\n");
    printf("���������1-5��");
    while( scanf("%d",&choice) == 0 || choice < 0 || choice > 5){
        printf("���벻�Ϸ���������1-5֮�������");
    }
    return choice;
}

void SAGTDFunc(database * originDB,treeNode * root,database * db){
    int maxDepth;
    float Pb;
    printf("��������󷺻����:");
    while(scanf("%d",&maxDepth) == 0 && maxDepth < 0 || maxDepth > treeHeight){
        printf("���벻�Ϸ���������%d-%d֮�����\n",0,treeHeight);
    }

    printf("������й¶������ֵ��");
    scanf("%f",&Pb);
    while(Pb < 0 || Pb > 1){
        printf("���벻�Ϸ���й¶������0-1֮��\n");
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
                printf("�������еĸ����ǣ�%d\n", A->count);
                break;

            case 2:
                Ts = SAGTD(originDB,db,root,maxDepth,Pb,maxDepth,1,SAGTDBreakFunc);
                printf("SAGTD���Ϊ��\n");
                sortDB(Ts);
                traverseDb(Ts,printRow);
                break;

            case 3:
                // todo ԭ�ڴ�δ�ͷ�
                db = initDb();
                migrate(db,DB_FILE_PATH_3);
                Ts = db;
                printf("���ý��Ϊ\n");
                traverseDb(db,printRow);
                break;

            case 4:
                Ts = SAGTD(originDB,db,root,maxDepth,Pb,maxDepth,0,SAGTDNonBreakFunc);
                printf("SAGTD���Ϊ��\n");
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