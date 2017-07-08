//
// Created by bian on 2017/7/4.
//
#ifndef PPTD_TREE_H
#define PPTD_TREE_H
#include <stdbool.h>
#include "stdio.h"
#include "../LinkedList/LinkedList.h"

#define Subset_Max_Length 20    // 叶子结点的最大数目
#define childListsLength 5      // 子节点最大数目（根据论文中的树！！！Pul下面的子树数目是有很大影响的）
#define treeHeight 3    // 树的高度
#define CONFIG_PATH "C:\\Users\\bian\\Desktop\\code\\PPTD\\config\\sensitive_tree.txt"
#define MAX_TEXT_LEN 100
#define QUEUE_LEN 28        // 广度优先遍历队列最大长度

typedef struct treeNode{
    struct treeNode * parent;
    struct treeNode * childLists[childListsLength];    // 最大四个子节点
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