//
// Created by bian on 2017/7/3.
//

#ifndef PPTD_LINKEDLIST_H
#define PPTD_LINKEDLIST_H
#include <stdio.h>
#include <malloc.h>

// 结点结构，头节点不存放数据
typedef struct LinkedNode{
    int data;
    struct LinkedNode *next;
}LinkedNode;

// 创建链表，指针函数参数为数据源长度
LinkedNode * listCreate(int *(* dataSource)(int *len));

// 删除第pos个结点
int listNodeDelete(LinkedNode * head, int pos);

// 销毁
void listDestroy(LinkedNode * head);

// 在第pos个有效元素前插入
LinkedNode * listInsert(LinkedNode * head, int pos, int val);

// 得到链表长度
int getListLength(LinkedNode * head);

// 得到第pos个节点
LinkedNode * getNode(LinkedNode * head, int pos);

// 遍历链表并用回调函数操作结点
void traverseList(LinkedNode * head, int (* pfun)(int));

void _t_linkedlist_main();

#endif //PPTD_LINKEDLIST_H
