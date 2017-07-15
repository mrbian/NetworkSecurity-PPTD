//
// Created by bian on 2017/7/4.
//
#ifndef PPTD_TREE_H
#define PPTD_TREE_H
#include <stdbool.h>
#include "stdio.h"
#include "../LinkedList/LinkedList.h"
#include "../config/config.h"

typedef struct treeNode{
    struct treeNode * parent;
    struct treeNode * childLists[childListsLength];    // 最大五个子节点
    char text[MAX_TEXT_LEN];                // 事先分配好空间
    int parentId;
    int selfId;
} treeNode;

// 初始化一个结点
treeNode * initOneNode(int selfId,int parentId,char * text);

// 数据初始化
treeNode * migrateTree(char* filePath);

// 所给数据插入树中
bool insertNodeToTree(treeNode * root, treeNode * node);

// 根据结点的Id得到结点
treeNode * getNodeById(treeNode* root, int id);

// 根据文本得到结点
treeNode * getNodeByText(treeNode *root, char *text);

// 得到结点高度
int getNodeHeight(treeNode* root, treeNode * node);

// 广度优先遍历树
void traverseTree(treeNode * root, void (*pfunc)(treeNode *));

// 得到所给结点的祖先节点，不包括自己
treeNode ** getCoverNodes(treeNode * root, treeNode * node);

// 判断结点是否被cover，相等false
bool nodeAisCoveredByNodeB(treeNode * root, treeNode * A, treeNode * B);

// 得到所有子树叶子
treeNode ** getSubsetsOfNode(treeNode * node);

// 得到所有子树集合的长度
int getSubsetsLengthOfNode(treeNode * node);

void _printText(treeNode * node);

void _tree_main();

#endif