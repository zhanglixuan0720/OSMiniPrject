#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *file = NULL;
    int PCB_num = 0, count = 0, arrive_time_pre = 0, status = 0;
    file = fopen("../PCBFile.txt", "w+"); //   file name
    srand(time(NULL));
    printf("Please input the number of PCB you want to get!\nPCB number:");
    scanf("%d", &PCB_num);
    while (PCB_num > 0)
    {
        // id priority arrive_time run_time used_time status
        status = fprintf(file, "%d %d  %d  %d  0  1\n", 1000 + count, rand() % 30, arrive_time_pre, rand() % 30);
        if (status < 0)
        {
            printf("Error in printing string to file.");
            return 1;
        }
        ++count;
        --PCB_num;
        arrive_time_pre += rand() % 5;
    }
    fclose(file);
    printf("Generate PCB parameters sucessfully.\n");
    return 0;
}