//
// Created by bian on 2017/7/4.
//
#include <mem.h>
#include "queue.h"
#include "../config/config.h"

// 存储n个元素
void initQueue(Queue * queue, int n, size_t t_size){
    queue->queue = NULL;
    queue->queue = (T *)malloc(t_size * n);
    if(queue->queue == NULL){
        printf("out of memory\n");
        exit(-1);
    }
    queue->front = queue->rear = 0;
    queue->maxSize = n + 1;
    queue->dataSize = t_size;
}

bool isEmpty(Queue * queue){
    return queue->front == queue->rear;
}

bool isFull(Queue * queue){
    return (queue->rear + 1) % queue->maxSize == queue->front;
}

bool enQueue(Queue * queue, T val){
    if(isFull(queue)){
        printf("out of queue\n");
        return false;
    }
    memcpy(&queue->queue[queue->rear], &queue + 1, sizeof(queue->dataSize));
    queue->rear = (queue->rear + 1) % queue->maxSize;
    return true;
}

bool outQueue(Queue * queue, T * val){
    if(isEmpty(queue)){
        printf("queue is empty\n");
        return false;
    }
    memcpy(val,&queue->queue[queue->front],sizeof(queue->dataSize));
    queue->front = (queue->front + 1) % queue->maxSize;
    return true;
}

void freeQueue(Queue * queue){
    free(queue->queue);
    free(queue);
    queue = NULL;
}

T * getFront(Queue * queue){
    if(isEmpty(queue)){
        return NULL;
    }
    return queue->queue[queue->front];
}

void traverseQueue(Queue * queue, void (*callback)(T)){
    int i = 0;
    for(i = queue->front; i < queue->rear; i ++){
        callback(queue->queue[i]);
    }
}

void _printData(T data){
    printf("the value is %d\n",data);
}

void _t_queue_main(){
    Queue * queue = (Queue *)malloc(sizeof(Queue));
    int val = 0;
    initQueue(queue, 3, sizeof(int));
    enQueue(queue, 1);
    enQueue(queue, 2);

    traverseQueue(queue,_printData);

    outQueue(queue,&val);
    printf("the top is %d\n",val);

    traverseQueue(queue,_printData);
}