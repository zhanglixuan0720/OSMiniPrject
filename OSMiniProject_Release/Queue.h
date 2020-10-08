#ifndef QUEUE_H
#define QUEUE_H
#include "PCB.h"

typedef struct QueueElement
{
    struct PCB *pcb;
    struct QueueElement *next;
    int key_word; //priority
} QueueElement;

typedef struct
{
    struct QueueElement *header;
    int elem_num;
} Queue;

void InitQueue(Queue *Q);               //init the queue
void PushDe(Queue *Q, QueueElement *e); //keyword decrease push, the maxium keyword is the first element in queue.
void PushIn(Queue *Q, QueueElement *e); //keyword increase push, contrary to PushDe.
QueueElement *Pop(Queue *Q);            // Get the first element from queue.

#endif
