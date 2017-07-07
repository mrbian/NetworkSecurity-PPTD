//
// Created by bian on 2017/7/4.
//
#include <mem.h>
#include "tree.h"
#include "../Queue/queue.h"

// 初始化一个结点
treeNode * initOneNode(int selfId, int parentId, char * text){
    treeNode * p = (treeNode *)malloc(sizeof(treeNode));
    p->selfId = selfId;
    p->parentId = parentId;
    p->parent = NULL;
    strcpy(p->text,text);
    int i;
    for(i = 0;i<childListsLength;i++){
        p->childLists[i] = NULL;
    }
    return p;
}

treeNode * migrateTree(char* filePath){
    // 论文中属性树的生成
    int selfId;
    int parentId;
    char * text = (char *)malloc(MAX_TEXT_LEN * sizeof(char));

    FILE *fp;
    if((fp=fopen(filePath,"r")) == NULL){
        printf("file operate fail\n");
        exit(-1);
    }

    fscanf(fp,"%d,%d,%[^\f\n\t\v\r]",&selfId,&parentId,text);
    treeNode * root = initOneNode(selfId,parentId,text);
    text = (char *)malloc(MAX_TEXT_LEN * sizeof(char));

    while(fscanf(fp,"%d,%d,%[^\f\n\t\v\r]",&selfId,&parentId,text) != EOF){
        insertNodeToTree(root,initOneNode(selfId,parentId,text));
        text = (char *)malloc(MAX_TEXT_LEN * sizeof(char));         // 重新开辟存储下一行text
    }
    fclose(fp);

    return root;
}

treeNode * getNodeById(treeNode * root, int id){
    treeNode * pt = root;
    Queue * queue = (Queue *)malloc(sizeof(Queue));
    initQueue(queue, QUEUE_LEN, sizeof(treeNode));
    enQueue(queue,pt);

    int i = 0;
    while(! isEmpty(queue)){
        outQueue(queue, &pt);
        if(pt->selfId == id)
            return pt;
        for(i = 0; i < childListsLength; i++){
            if(pt->childLists[i] != NULL)
                enQueue(queue,pt->childLists[i]);
        }
    }
    return NULL;
}

treeNode * getNodeByText(treeNode *root, char *text){
    treeNode * pt = root;
    Queue * queue = (Queue *)malloc(sizeof(Queue));
    initQueue(queue, QUEUE_LEN, sizeof(treeNode));
    enQueue(queue,pt);

    int i = 0;
    while(! isEmpty(queue)){
        outQueue(queue, &pt);
        if(strcmp(pt->text,text) == 0)
            return pt;
        for(i = 0; i < childListsLength; i++){
            if(pt->childLists[i] != NULL)
                enQueue(queue,pt->childLists[i]);
        }
    }
    return NULL;
}

bool insertNodeToTree(treeNode * root, treeNode * node){
    int parentId = node->parentId;
    treeNode * parentNode = getNodeById(root, parentId);
    if(parentNode == NULL){
        printf("node's id is illegal\n");
        return false;
    }
    int i;
    for(i=0;i<childListsLength;i++){
        if(parentNode->childLists[i] != NULL)
            continue;
        else{
            parentNode->childLists[i] = node;
            node->parent = parentNode;
            return true;
        }
    }
    printf("the space of sub-tree is full\n");
    return false;
}

// 广度优先遍历此树
void traverseTree(treeNode * root, void (*pfunc)(treeNode *)){
    treeNode * pt = root;
    Queue * queue = (Queue *)malloc(sizeof(Queue));
    initQueue(queue, QUEUE_LEN, sizeof(treeNode));
    enQueue(queue,pt);

    int i = 0;
    while(! isEmpty(queue)){
        outQueue(queue, &pt);
        pfunc(pt);        // 访问
        for(i = 0; i < childListsLength; i++){
            if(pt->childLists[i] != NULL)
                enQueue(queue,pt->childLists[i]);
        }
    }
}

int getNodeHeight(treeNode * root, treeNode * node){
    if(node == NULL){
        printf("check the node, node is illegal\n");
        exit(-1);
    }
    int h = treeHeight;
    treeNode * pt = node;
    while(pt->parent != NULL && pt != root){
        pt = pt->parent;
        h --;
    }
    return h;
}

treeNode ** getCoverNodes(treeNode * root, treeNode * node){
    if(node == NULL){
        printf("node is null, do not have cover nodes\n");
        exit(-1);
    }
    treeNode ** coverNodes = (treeNode **)malloc(sizeof(treeNode *) * treeHeight);  // 最多三个
    int i = 0;
    for(i=0;i<treeHeight && node != NULL;i++){      // node != NULL
        if(node->parent != NULL){
//            coverNodes[i] = (treeNode *)malloc(sizeof(treeNode));
            coverNodes[i] = node->parent;
        }else
            coverNodes[i] = NULL;

        node = node->parent;
    }
    return coverNodes;
}

treeNode ** getSubsetsOfNode(treeNode * node){
    if(node == NULL){
        printf("node is null\n");
        exit(-1);
    }

    int i,flag;
    int count = 0;
    treeNode ** nodesCollection = (treeNode **)malloc(sizeof(treeNode *) * Subset_Max_Length);
    for(i=0;i<Subset_Max_Length;i++){
        nodesCollection[i] = NULL;
    }

    treeNode * pt = node;
    Queue * queue = (Queue *)malloc(sizeof(Queue) * Subset_Max_Length);
    initQueue(queue, QUEUE_LEN, sizeof(treeNode));

    enQueue(queue,pt);
    while(!isEmpty(queue)){
        flag = 1;               // 假定是叶子
        outQueue(queue,&pt);
        for(i=0;i<childListsLength;i++){
            if(pt->childLists[i] != NULL){
                flag = 0;
                enQueue(queue,pt->childLists[i]);
            }
        }
        if(flag){       // 如果是叶子
            nodesCollection[count] = pt;
            count ++;
        }
    }
    return nodesCollection;
}

int getSubsetsLengthOfNode(treeNode * node){
    if(node == NULL){
        printf("node is null\n");
        exit(-1);
    }

    int i,flag;
    int count = 0;
    treeNode * pt = node;
    Queue * queue = (Queue *)malloc(sizeof(Queue) * Subset_Max_Length);
    initQueue(queue, QUEUE_LEN, sizeof(treeNode));

    enQueue(queue,pt);
    while(!isEmpty(queue)){
        flag = 1;               // 假定是叶子
        outQueue(queue,&pt);
        for(i=0;i<childListsLength;i++){
            if(pt->childLists[i] != NULL){
                flag = 0;
                enQueue(queue,pt->childLists[i]);
            }
        }
        if(flag)
            count ++;
    }
    return count;
}

bool nodeAisCoveredByNodeB(treeNode * root, treeNode * A, treeNode * B){
    if(A == NULL || B== NULL){
        printf("node A or B is illegal\n");
        exit(-1);
    }
    treeNode ** nodesCollection = getCoverNodes(root,A);
    int i;
    bool flag = false;
    for(i=0;i<treeHeight;i++){
        if(nodesCollection[i] == B){
            flag = true;
            break;
        }
    }
    return flag;
}

void _printText(treeNode * node){
    printf("%s\n",node->text);
}

void _tree_main(){
    treeNode * root = migrateTree(CONFIG_PATH);

    // result
//    traverseTree(root,_printText);

    // 得到祖先结点
//    treeNode** nodesCollection = getCoverNodes(root,getNodeByText(root,"High Blood Sugar"));
//    int i = 0;
//    for(i=0;i<treeHeight;i++){
//        if(nodesCollection[i] != NULL)
//            printf("%s\n",nodesCollection[i]->text);
//    }

//    treeNode * pt = getNodeByText(root,"Pulmonary Disease");
//    printf("%s\n",pt->text);
//    printf("the subsets length of PD is %d",getSubsetsLengthOfNode(pt));

//    printf("the height of High Blood Sugar is %d\n",getNodeHeight(root,getNodeByText(root,"High Blood Sugar")));

//    treeNode * A = getNodeByText(root,"Lung Infection");
//    treeNode * B = getNodeByText(root,"Pulmonary Disease");
//    printf("node A is Covered by node B? %d",nodeAisCoveredByNodeB(root,A,B));

    treeNode ** nodesC = getSubsetsOfNode(getNodeByText(root,"Lung Infection"));
    int j = 0;
    for(j=0;j<Subset_Max_Length;j++){
        if(nodesC[j] != NULL){
            printf("one of subsets is %s\n",nodesC[j]->text);
        }
    }
}