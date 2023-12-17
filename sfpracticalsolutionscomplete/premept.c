#include<stdio.h>
#define size 100
#include <limits.h>
void calculation(int burst_time[],int arrival_time[],int process[],int n);
void main(){
    int burst_time[size];
    int arrival_time[size];
    int process[size];
    int n;
    printf("\tWELCOME TO SRTF CALCULATOR\t \n");
    printf("\nRonit Satish Mehta 60009230207\n");
    printf("\nEnter the number of process:\n");
    scanf("%d",&n);
    printf("\nEnter the process number:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&process[i]);
    }
    
    printf("\nEnter the burst time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&burst_time[i]);
    }
    printf("\n Enter the arrival time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arrival_time[i]);
    }
    printf("\nthe table for SRTF is as follow:\n");
    printf("pn \t bt \t at\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\n",process[i],burst_time[i],arrival_time[i]);
    }
    
     calculation(burst_time,arrival_time,process,n);
}
void calculation(int burst_time[],int arrival_time[],int process[],int n){
    int gt[100] = {0};
    int tt[100] = {0};
    int wt[100] = {0};
    int waiting_time =0;
    float avg_waiting_time = 0.0;
    int turnaround_time = 0;
    float avg_turnaround_time = 0.0;
    int remaining_time[100];
    int current_time = 0;
    int completed = 0;
    int completion_time[100];
    for (int i = 0; i < n; i++)
    {
        remaining_time[i] = burst_time[i];
    }
    while (completed<n)
    {
        int min_time = INT_MAX;
        int shortest_process = -1;
        for (int i = 0; i < n; i++)
        {
            if (arrival_time[i] <= current_time && remaining_time[i] <= min_time && remaining_time[i] > 0)
            {
                shortest_process = i;
                min_time = remaining_time[i];
            }
            
        }
        if (shortest_process == -1)
        {
            current_time++;
        }
        else
        { 
            remaining_time[shortest_process]--;
            if (remaining_time[shortest_process] == 0)
            {
                completed++;
                int end_time = current_time + 1;
                tt[shortest_process] = end_time - arrival_time[shortest_process];
                wt[shortest_process] = tt[shortest_process] - burst_time[shortest_process];
                current_time = end_time;
                waiting_time+=wt[shortest_process];
                turnaround_time+=tt[shortest_process];
                completion_time[shortest_process]=end_time;
            }
            else
            {
                current_time++;
            }
            
        }
        
    }
    avg_turnaround_time = (float) turnaround_time/n;
    avg_waiting_time = (float) waiting_time/n;
    printf("\nwaiting:%f",avg_waiting_time);
    printf("\nturnaround:%f",avg_turnaround_time);
}
void calculation_round_robin(int burst_time[],int arrival_time[],int process[],int n){
    int time_quantmn;
    int gt[100] = {0};
    int i = 0;
    int time = 0;
    int remaining_time[100];
    int wt[100] = {0};
    int tt[100] = {0};
    int completion_time[100] = {0};
    int waiting_time = 0;
    float avg_waiting_time = 0.0;
    float avg_turnaround_time = 0.0;
    int turnaround_time = 0;
    printf("\nEnter time quantumn:");
    scanf("%d",&time_quantmn);
    for (int i = 0; i < n; i++)
    {
        remaining_time[i] = burst_time[i];
    }
    while (1)
    {
        int done = 1;
        for (int i = 0; i < n; i++)
        {
            if (remaining_time[i] > 0)
            {
                done =0;
                if (remaining_time[i] <= time_quantmn)
                {
                    time+=remaining_time[i];
                    completion_time[i] = time;
                    remaining_time[i] = 0;
                }
                else
                {
                    time+=time_quantmn;
                    remaining_time[i] -= time_quantmn;
                }
                
            }

        }
        if(done) break;
    }
    for (int i = 0; i < n; i++)
    {
        tt[i]= completion_time[i] - arrival_time[i];
        wt[i]=tt[i] - burst_time[i];
    }
    for (int i = 0; i < n; i++)
    {
        waiting_time+=wt[i];
        turnaround_time+=tt[i];
    }
    avg_waiting_time = (float) waiting_time/n;
    avg_turnaround_time = (float) turnaround_time/n;
    printf("\navg waiting time:%f",avg_waiting_time);
    printf("\navg turnaround time:%f",avg_waiting_time);
}
void calculation_priority(int burst_time[],int arrival_time[],int process[],int n){
    int priority[100];
    int gt[100]={0};
    int wt[100]={0};
    int tt[100]={0};
    int waiting_time=0;
    int turnaround_time=0;
    float avg_waiting_time=0.0;
    float avg_turnaround_time=0.0;
    int remaining_time[100]={0};
    int current_time=0;
    int completed=0;
    int completion_time[100]={0};
    for (int i = 0; i < n; i++)
    {
        remaining_time[i] = burst_time[i];
    }
    while(completed<n)
    {
        int shortest_process=-1;
        int min_prio = INT_MAX;
        for (int k = 0; k < n; k++)
        {
            if (arrival_time[k]<=current_time && priority[k] <= min_prio && priority[k] > 0)
            {
                min_prio = priority[k];
                shortest_process=k;
            }
        }
        if (shortest_process == -1)
        {
            current_time++;
        }
        else
        {
            remaining_time[shortest_process]--;
            if (remaining_time[shortest_process] == 0)
            {
                 completed++;
                 int end_time= current_time+1;
                 tt[shortest_process]= end_time-arrival_time[shortest_process];
                 wt[shortest_process] = tt[shortest_process] - burst_time[shortest_process];
                 current_time = end_time;
                 completion_time[shortest_process] = end_time;
                 waiting_time+=wt[shortest_process];
                 turnaround_time+=tt[shortest_process];
            }
            else
            {
                current_time++;
            }
        }
    }
    avg_turnaround_time = (float) turnaround_time/n;
    avg_waiting_time = (float) waiting_time/n;
    printf("\navg waiting time:%f",avg_waiting_time);
    printf("\ntavg turnaround time:%f",avg_turnaround_time);
    

}