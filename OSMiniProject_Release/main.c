#include <stdio.h>
#include "PCB.h"
#include "Queue.h"
#include <stdlib.h>
int PCBRead(FILE *file, Queue *Q, int algorithm);                                   //read the pcb information from appointed file
void PCBPrint(QueueElement *e);                                                     //print the pcb information
void SchedulePrint(Queue *ready_queue, Queue *finished_queue);                      //print the process id in ready queue and finished queue
void PrintAllPCB(Queue *ready_queue, Queue *finished_queue);                        //print all pcb information in queues.
void PrioritySchedule(Queue *ready_queue, Queue *finished_queue, int *system_time); // priority schedule method
void FCFSSchedule(Queue *ready_queue, Queue *finished_queue, int *system_time);     //first come first serve schedule method

int main(int argc, char **argv)
{
    int system_time = 0, status = 0, algorithm = 0; // 0 : priority 1: fcfs
    Queue ready_queue, finished_queue;
    Queue *Q = (Queue *)malloc(sizeof(Queue)); //Q is crated for getting the created QueueElement
    FILE *pcb_file = NULL;
    InitQueue(&ready_queue);
    InitQueue(&finished_queue);

    pcb_file = fopen("../PCBFile.txt", "r");

    printf("Please input the schedule method you want to use (you can choose the 0: priority schedule, 1: fcfs schedule): ");
    scanf("%d", &algorithm);
    printf("schedule algorithm: %d\n", algorithm);
    status = PCBRead(pcb_file, Q, algorithm);

    while (1)
    {
        // read arrived process
        while (system_time == Q->header->pcb->arrive_time)
        {
            switch (algorithm)
            {
            case 0:
                PushDe(&ready_queue, Q->header);
                break;
            case 1:
                PushIn(&ready_queue, Q->header);
                break;
            default:
                printf("No required algoritm exist.");
                break;
            }
            if (status >= 0)
            {
                status = PCBRead(pcb_file, Q, algorithm);
                if (status < 0)
                {
                    Q->header->pcb->arrive_time = -1;
                    break;
                }
            }
        }

        //system time print
        printf("----------------------------------------------\n");
        printf("system time:  %d\n", system_time);

        ++system_time;

        //check the ready quque
        if (!ready_queue.elem_num)
        {

            printf("Waiting for processes arriving...\n");
            if (system_time > 1024 * 32)
            {
                printf("Waiting two much time, Schedule process exit normally.\n");

                break;
            }
            printf("\033[3A"); // upwards three rows

            continue;
        }

        //shedule & PCB Information
        SchedulePrint(&ready_queue, &finished_queue);
        PrintAllPCB(&ready_queue, &finished_queue);

        //schedule
        switch (algorithm)
        {
        case 0:
            PrioritySchedule(&ready_queue, &finished_queue, &system_time);
            break;
        case 1:
            FCFSSchedule(&ready_queue, &finished_queue, &system_time);
            break;
        default:
            printf("No required algoritm exist.");
            break;
        }
    }

    fclose(pcb_file);
    return 0;
}

int PCBRead(FILE *file, Queue *Q, int algorithm)
{
    int status = 1;
    PCB *pcb = (PCB *)malloc(sizeof(PCB));
    QueueElement *e = (QueueElement *)malloc(sizeof(QueueElement));
    // id priority arrive_time run_time used_time status
    status = fscanf(file, "%d  %d  %d  %d  %d  %d\n", &pcb->process_id, &pcb->priority, &pcb->arrive_time, &pcb->run_time, &pcb->used_time, &pcb->process_status);
    e->pcb = pcb;

    e->next = 0;

    switch (algorithm)
    {
    case 0:
        e->key_word = pcb->priority;
        break;
    case 1:
        e->key_word = pcb->arrive_time;
        break;
    default:
        printf("No required algoritm exist.");
        status = -1;
        break;
    }
    Q->header = e;
    e = 0;
    pcb = 0; // prevent system from  freeing the pcb
    return status;
}

void PCBPrint(QueueElement *e)
{
    PCB *pcb = e->pcb;
    // id priority arrive_time run_time used_time status
    printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t", pcb->process_id, e->key_word, pcb->priority, pcb->arrive_time, pcb->run_time, pcb->used_time);
    switch (pcb->process_status)
    {
    case 1:
        printf("Wait\n");
        break;
    case 2:
        printf("Run\n");
        break;
    case 3:
        printf("Finish\n");
        break;
    default:
        printf("No required Status exist.");
        break;
    }
}
void SchedulePrint(Queue *ready_queue, Queue *finished_queue)
{
    QueueElement *q = ready_queue->header;
    if (q)
    {
        printf("Running Process (ID):  %d\n", q->pcb->process_id);
        q = q->next;
    }

    printf("Ready Queue (ID):  ");
    while (q)
    {
        printf("%d    ", q->pcb->process_id);
        q = q->next;
    }
    printf("\n");

    printf("Finished Queue (ID):  ");
    q = finished_queue->header;
    while (q)
    {
        printf("%d    ", q->pcb->process_id);
        q = q->next;
    }
    printf("\n");
}

void PrintAllPCB(Queue *ready_queue, Queue *finished_queue)
{
    QueueElement e, *q;
    printf("PCB:\n");
    printf("ID\tKeyword\t\tPriority\tArrive Time\tRun Time\tUsed Time\tStatus\n");
    if (ready_queue->header)
    {
        e = *(ready_queue->header);
        e.pcb->process_status = Run;
        PCBPrint(&e);
        q = e.next;
    }
    else
    {
        q = ready_queue->header;
    }

    while (q)
    {
        PCBPrint(q);
        q = q->next;
    }

    q = finished_queue->header;
    while (q)
    {
        PCBPrint(q);
        q = q->next;
    }
}

void PrioritySchedule(Queue *ready_queue, Queue *finished_queue, int *system_time)
{
    QueueElement *e = Pop(ready_queue);

    e->pcb->process_status = Run;

    ++e->pcb->used_time;
    e->next = 0;
    if (e->pcb->used_time >= e->pcb->run_time)
    {
        e->key_word = *system_time;
        e->pcb->process_status = Finish;
        PushIn(finished_queue, e);
    }
    else
    {
        --e->key_word;
        e->pcb->process_status = Wait;
        PushDe(ready_queue, e);
    }
}

void FCFSSchedule(Queue *ready_queue, Queue *finished_queue, int *system_time)
{
    QueueElement *e = Pop(ready_queue);

    //Pop(ready_queue, e);
    e->pcb->process_status = Run;

    ++e->pcb->used_time;
    e->next = 0;
    if (e->pcb->used_time >= e->pcb->run_time)
    {
        e->key_word = *system_time;
        PushIn(finished_queue, e);
    }
    else
    {
        PushIn(ready_queue, e);
    }
}