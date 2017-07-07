//
// Created by bian on 2017/7/3.
//
#include "LinkedList.h"

// 根据dataSource函数返回的数组生成链表
LinkedNode * listCreate(int *(* dataSource)(int *)){
    int i;
    int len;
    int * dataCollection = dataSource(&len);
    if(dataCollection == NULL){
        printf("data resource is illegal, make it static\n");
        exit(-1);
    }

    LinkedNode * phead = (LinkedNode *)malloc(sizeof(LinkedNode));
    if(phead == NULL){
        printf("out of memory, create list fail\n");
        exit(-1);
    }
    else{
        LinkedNode * ptail = phead;
        ptail->next = NULL;

        for(i=0;i<len;i++){
            LinkedNode * pt = (LinkedNode *)malloc(sizeof(LinkedNode));
            if(pt == NULL){
                printf("out of memory, create list fail\n");
                exit(-1);
            }
            pt->data = dataCollection[i];
            ptail->next = pt;
            pt->next = NULL;
            ptail = pt;
        }

        return phead;
    }
}

// 删除第pos个节点
int listNodeDelete(LinkedNode * head, int pos){
    if(head == NULL || head->next == NULL || pos < 1){
        return 0;
    }
    LinkedNode * pt = head;
    LinkedNode * pf = NULL;
    int i = 0;
    while (i < pos - 1){    // 找到第i-1个点
        pt = pt->next;
        i++;
    }
    if(pt->next == NULL){
        return 0;
    }
    pf = pt->next;
    pt->next = pt->next->next;
    free(pf);
    pf = NULL;  // 防止野指针
    return 1;
}

// 摧毁链表
void listDestroy(LinkedNode *head){
    while(listNodeDelete(head,1));
    free(head);
}

// 得到第pos个有效元素
LinkedNode * getNode(LinkedNode * head, int pos){
    if(pos < 1){
        return NULL;
    }
    int i = 0;
    LinkedNode * p = head;
    while(p->next != NULL && i < pos-1){       // 找到第pos个有效元素
        p = p->next;
        i++;
    }
    return p->next;
}

// 第pos个有效元素(非头节点)前插入元素
LinkedNode * listInsert(LinkedNode * head, int pos, int val){
    LinkedNode* pt = getNode(head,pos - 1);     // 得到第pos-1个
    if(pt == NULL || pt->next == NULL){         // 如果pt空或没有第pos个
        return NULL;
    }
    LinkedNode* p = (LinkedNode*)malloc(sizeof(LinkedNode));
    p->data = val;
    p->next = pt->next;
    pt->next = p;
    return p;
}

// 得到链表长度
int getListLength(LinkedNode * head){
    int len = 0;
    LinkedNode * pt = head;
    while(pt->next != NULL){
        len ++;
        pt = pt->next;
    }
    return len;
}

// 遍历链表
void traverseList(LinkedNode * head, int (* pfun)(int)){
    LinkedNode * pt = NULL;
    pt = head->next;
    int result;
    while(pt != NULL){
        result = pfun(pt->data);
        if(result == 0){
            printf("operate fail of %d\n",pt->data);
            break;
        }
        pt = pt->next;
    }
}

int * _getData(int *len){
    static int data[] = {1,2,3,4};
    *len = sizeof(data) / sizeof(data[0]);
    return data;
};

// 打印数据
int printData(int data){
    printf("the data of node is %d\n", data);
    return 1;
}

void _t_linkedlist_main(){
    LinkedNode * head = listCreate(_getData);
    traverseList(head,printData);

    int len = getListLength(head);
    printf("the length of list is %d\n\n",len);

    listInsert(head,3,10);
    traverseList(head,printData);

//    listNodeDelete(head,1);
//    traverseList(head,printData);
//
//    listDestroy(head);
}