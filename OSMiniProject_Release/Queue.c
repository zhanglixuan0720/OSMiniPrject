#include "Queue.h"

void InitQueue(Queue *Q)
{
    Q->header = 0;
    Q->elem_num = 0;
}

void PushDe(Queue *Q, QueueElement *e)
{
    QueueElement *pl, *p;
    if (!Q->elem_num)
    {
        Q->header = e;
    }
    else
    {
        pl = 0;
        p = Q->header;
        while (p && p->key_word > e->key_word)
        {
            pl = p;
            p = p->next;
        }
        e->next = p;
        if (pl)
        {
            pl->next = e;
        }
        else
        {
            Q->header = e;
        }
    }
    ++Q->elem_num;
}
void PushIn(Queue *Q, QueueElement *e)
{
    QueueElement *pl, *p;
    if (!Q->elem_num)
    {
        Q->header = e;
    }
    else
    {
        pl = 0;
        p = Q->header;
        while (p && p->key_word < e->key_word)
        {
            pl = p;
            p = p->next;
        }
        e->next = p;
        if (pl)
        {
            pl->next = e;
        }
        else
        {
            Q->header = e;
        }
    }
    ++Q->elem_num;
}
QueueElement *Pop(Queue *Q)
{

    QueueElement *e = Q->header;
    Q->header = e->next;
    --Q->elem_num;
    return e;
}