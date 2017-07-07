//
// Created by bian on 2017/7/3.
//

#ifndef PPTD_BINARYTREENODE_H
#define PPTD_BINARYTREENODE_H
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef int ElemType;
typedef struct BinTreeNode{
    ElemType data;
    struct BinTreeNode * left;
    struct BinTreeNode * right;
}BinTreeNode;

BinTreeNode * initTree(ElemType data);

// 排序方式插入构建二叉树
void insertNode(BinTreeNode * root,ElemType e);

bool isLeaf(BinTreeNode * node);

BinTreeNode * getLeftSibling(BinTreeNode * root, BinTreeNode * node);

BinTreeNode * getRightSibling(BinTreeNode * root, BinTreeNode * node);

BinTreeNode * getParent(BinTreeNode * root, BinTreeNode * node);

void levelOrder(BinTreeNode * root, void (* visit)(BinTreeNode *));

void _t_tree_main();

#endif //PPTD_BINARYTREENODE_H
