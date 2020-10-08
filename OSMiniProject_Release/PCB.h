#ifndef PCB_H
#define PCB_H
enum ProcessStatus
{
    Wait = 1,
    Run = 2,
    Finish = 3
};
typedef struct PCB
{
    int process_id;
    int priority;
    int arrive_time;
    int run_time;
    int used_time;
    enum ProcessStatus process_status;
} PCB;

#endif