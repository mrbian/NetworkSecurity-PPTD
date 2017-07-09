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

//#define �� 2
//#define �� 0.5

// ��ѭ����ӡ����
int inputChoice(){
    int choice;
    printf("--------------------------------------PPTD--------------------------------------\n");
    printf("1�������ǰ���ݿ�\n");
    printf("2��������ȱ����������������\n");
    printf("3�����빥�����м��㵱ǰ���ݿ�ĳ��й¶����\n");
    printf("4���Ե�ǰ���ݿ�ʵʩSAGTD�㷨��������󷺻���Ⱥ�й¶������ֵ���鿴����\n");
    printf("5���Ե�ǰ���ݿ�ʵʩMPSTD�㷨��������󷺻���Ⱥ�й¶������ֵ���鿴���̣��Զ�����һ��SAGTD��\n");
    printf("6�����ԭʼ���ݿ�\n");
    printf("7���������ݿ�\n");
    printf("8���˳�����\n");
    printf("������1-8ѡ����Ӧ��ѡ�");
    scanf("%d",&choice);
    if(choice > 8 || choice < 1){
        printf("���벻�Ϸ�\n");
        return -1;
    }
    return choice;
}

// 3�����빥�����м���й¶���ʺ���
void caculateFunc(database * originDB,treeNode * root, database *db){
    while(1){
        int row_id, t_count = 1, i = 0;
        char ** track;
        printf("��ǰ���ݿ�Ϊ��\n");
        traverseDb(db,printRow);

        printf("�����빥�����и�����");
        scanf("%d", &t_count);
        printf("�����빥�����У�");
        track = (char **)malloc(sizeof(char *) * t_count);
        while(i < t_count){
            track[i] = (char *)malloc(sizeof(char) * 3);
            scanf("%s",track[i]);
            i++;
        }
        trackRow * row = initOneRow(track,t_count);

        printf("�������������е�id��");
        scanf("%d",&row_id);
        while(row_id > 7 || row_id < 1){
            printf("���벻�Ϸ������������룻\n");
            printf("��������id��");
            scanf("%d",&row_id);
        }

        printf("���е�й¶������: %-5.2f\n", caculateBreachProbability(originDB,db,root,row_id,row->tracks,row->count));
        printf("�س�������һ�μ��㣬���������ַ��˳�\n");

        // ���stdin
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
    printf("��������󷺻����:");
    while(scanf("%d",&maxDepth) == 0 && maxDepth < 0 || maxDepth > treeHeight){
        printf("���벻�Ϸ���������%d-%d֮�����\n",0,treeHeight);
    }

    printf("������й¶������ֵ��");
    scanf("%f",&PbThreshold);
    while(PbThreshold < 0 || PbThreshold > 1){
        printf("���벻�Ϸ���й¶������0-1֮��\n");
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
                printf("ԭʼ���ݿ���\n");
                traverseDb(originDB,printRow);
                break;

            case 7:
                // todo : ԭ�ڴ�δ�ͷ�
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

    // ֱ�ӽ��
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
