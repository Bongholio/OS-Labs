// C program for implementation of FCFS  scheduling (not preemptive)


#include<stdio.h>
#include <stdlib.h>

//Function to calculate average time
void findavgTime(int processes[], int n, int bt[])
{
    int *wt, *tat, *bt_copy, total_wt = 0, total_tat = 0;

    wt = calloc(n * sizeof(int), 1);         // set to '0'
    if (!wt)
    {
        printf("findavgTime: fail allocated WT");
        return;
    }

    tat = calloc(n * sizeof(int), 1);
    if (!tat)
    {
        printf("findavgTime: fail allocated TAT");

        // David: here is a bug - what it is ?
        return;
    }

    bt_copy = calloc(n * sizeof(int), 1);
    if (!bt_copy)
    {
        printf("findavgTime: fail allocated TAT");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        bt_copy[i] = bt[i];
    }

    int clock = 0;
    int curr_proc = 0;     // start fith 1st 

    while (1)      //   each iteration is a a clock
    {
        // update statistics
        for (int i = 0; i < n; i ++)
        {
            // wait time
            if (i > curr_proc)  wt[i]++;       // increment for those still waiting
            if (i >= curr_proc)  tat[i]++;      // increment for those still waiting and the running 
        }
        if (!(--bt_copy[curr_proc]))        // if completed, start the next process
        {
            curr_proc++;
            if (curr_proc == n)    break;      // the run completed
        }

        clock++;

/*
        printf("Clock = %d\n", clock);
        for (int i = 0; i < n; i ++ )
        {
            printf("proc  = %d  burst = %d wait = %d tat = %d\n", i, bt[i], wt[i], tat[i]);
        }
*/
    }

    //Display processes along with all details
    printf("Processes   Burst time   Waiting time   Turn around time\n");

    // Calculate total waiting time and total turn 
    // around time
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("   %d ", (i + 1));
        printf("           %d ", bt[i]);
        printf("            %d", wt[i]);
        printf("                %d\n", tat[i]);
    }
    float s = (float)total_wt / n;
    float t = (float)total_tat / n;
    printf("\n\n\n");
    printf("Average waiting time = %f \n\n", s);
    printf("Average turn around time = %f \n\n ", t);

    printf("Throughput = %f \n\n ", (float)tat[n - 1] / n);   // end of the last process divided by num. of processes
}


#define NUM_OF_PROCESSES   3
int main()
{
    //process id's
    int processes[NUM_OF_PROCESSES] = { 1, 2, 3 };

    //Burst time of all processes
    int  burst_time[NUM_OF_PROCESSES] = { 10, 5, 8 };

    printf(" FCFS (First Come First Served) - clock by clock \n\n");
    findavgTime(processes, NUM_OF_PROCESSES, burst_time);
    return 0;
}