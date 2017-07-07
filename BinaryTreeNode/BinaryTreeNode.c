//
// Created by bian on 2017/7/3.
//
#include "BinaryTreeNode.h"
#include "../Queue/queue.h"

BinTreeNode * initTree(ElemType data){
    BinTreeNode * root = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    root->left = NULL;
    root->right = NULL;
    root->data = data;
}

// 排序方式插入节点
void insertNode(BinTreeNode * root,ElemType e){
    if(root == NULL){
        printf("root node can not be null\n");
        exit(-1);
    }
    int left = 1;
    BinTreeNode * temp = NULL;
    BinTreeNode * pNode = root;
    while(pNode != NULL){
        temp = pNode;
        if(e == pNode->data)
            return;
        if(e < pNode->data){
            left = 1;
            pNode = pNode->left;
            continue;
        }
        if(e > pNode->data){
            left = 0;
            pNode = pNode->right;
            continue;
        }
    }
    BinTreeNode * p = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    p->data = e;
    p->left = p->right = NULL;
    left ? (temp->left = p) : (temp->right = p);
}

bool isLeaf(BinTreeNode * node){
    return node != NULL && node->left == NULL && node->right == NULL;
}

BinTreeNode * getLeftSibling(BinTreeNode * root, BinTreeNode * node){
    BinTreeNode * p = root;

}

// 广度优先遍历
void levelOrder(BinTreeNode * root, void (* visit)(BinTreeNode *)){
    BinTreeNode * pt = (BinTreeNode *)malloc(sizeof(BinTreeNode));

    Queue * queue = (Queue *)malloc(sizeof(Queue));
    initQueue(queue, 2, sizeof(BinTreeNode));
    enQueue(queue,root);

    while(! isEmpty(queue)){
        (BinTreeNode *)outQueue(queue, &pt);
        if(pt == NULL){
            printf("结点指针NULL\n");
            return;
        }
        visit(pt);
        if(pt->left != NULL)
            enQueue(queue,pt->left);
        if(pt->right != NULL)
            enQueue(queue,pt->right);
    }
}

void _visit(BinTreeNode * node){
    printf("the data of node is %d\n", node->data);
}

void _t_tree_main(){
    BinTreeNode * root = initTree(5);
    for(int i=0;i < 2;i++){
        insertNode(root,i);
    }
    levelOrder(root,_visit);
}