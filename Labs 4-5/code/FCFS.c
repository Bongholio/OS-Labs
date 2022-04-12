// C program for implementation of FCFS  scheduling (not preemptive)


#include<stdio.h>
#include <stdlib.h>

//Function to calculate average time
void findavgTime(int processes[], int n, int bt[])
{
    int *wt, *tat, total_wt = 0, total_tat = 0;

    wt = malloc(n * sizeof(int));
    if (!wt)
    {
        printf("findavgTime: fail allocated WT");
        return;
    }

    tat = malloc(n * sizeof(int));
    if (!tat)
    {
        printf("findavgTime: fail allocated TAT");

        // David: here is a bug - what it is ?
        return;
    }
     
    // Calculate waiting time for each process: by summ of wait time & burst time of the previous process 
    // ==================================================================================================
    // waiting time for first process is 0
    wt[0] = 0;

    // calculating waiting time
    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];   // wait time + burst time of previous process
       
    // calculating turnaround time by adding:  bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];

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

    printf("Throughput = %f \n\n ", (float)tat[n-1]/n);   // end of the last process divided by num. of processes

    // David: here is a bug - what it is ?
}


#define NUM_OF_PROCESSES   3
int main()
{
    //process id's
    int processes[NUM_OF_PROCESSES] = { 1, 2, 3 };
   
    //Burst time of all processes
    // int  burst_time[NUM_OF_PROCESSES] = { 10, 5, 8 };
    int  burst_time[NUM_OF_PROCESSES] = {  5, 8, 10  };

    printf(" FCFS (First Come First Served) \n\n");
    findavgTime(processes, NUM_OF_PROCESSES, burst_time);
    return 0;
}