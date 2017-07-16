//
// Created by bian on 2017/7/4.
//

#ifndef PPTD_QUEUE_H
#define PPTD_QUEUE_H
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

/**
 * 使用前不要忘记initQueue，否则enQueue会crash
 */
typedef void * T;
typedef struct Queue{
    T * queue;
    int maxSize;
    int front;
    int rear;
    size_t dataSize;
}Queue;

void initQueue(Queue * queue,int n, size_t t_size);

bool enQueue(Queue * queue, T val);

bool outQueue(Queue * queue, T * val);

bool isEmpty(Queue * queue);

bool isFull(Queue * queue);

void freeQueue(Queue * queue);

T * getFront(Queue * queue);

void traverseQueue(Queue * queue, void (*callback)(T));

void _t_queue_main();

#endif //PPTD_QUEUE_H
