#include<stdio.h>
void calculation(int process[],int bursttime[],int n,int arrival_time[]);
void calculation_sjf(int process[],int bursttime[],int n,int arrival_time[]);
void calculation_priority(int process[],int bursttime[],int n,int arrival_time[],int priority[]);
void main(){
    int process[100];
    int burst_time[100];
    int arrival_time[100];
    int n;
    int choice;
    int priority[100];
    printf("\nenter the number of process:");
    scanf("%d",&n);
    printf("\nenter the process id:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&process[i]);
    }
    printf("\nEnter burst time for each process:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&burst_time[i]);
    }
    printf("\nEnter arrival time for each provess:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arrival_time[i]);
    }
    do
    {
       printf("\n1.FCFS");
       printf("\n2.priority");
       printf("\n3.SJF");
       printf("\nenter choice:");
       scanf("%d",&choice);
       switch (choice)
       {
       case 1:
           printf("\nTable for FCFS is as follow:");
           printf("\npn\tbt\tat");
           for (int i = 0; i < n; i++)
           {
            printf("\n%d\t%d\t%d",process[i],burst_time[i],arrival_time[i]);
           }
          calculation(process,burst_time,n,arrival_time);
        break;
       case 2:
           printf("\nTable for SJF is as follow:");
           printf("\npn\tbt\tat");
           for (int i = 0; i < n; i++)
           {
              printf("\n%d\t%d\t%d",process[i],burst_time[i],arrival_time[i]);
           }
           calculation_sjf(process,burst_time,n,arrival_time);
       break;
       case 3:
           for (int i = 0; i < n; i++)
           {
             scanf("%d",&priority[i]);
           }
           printf("\nTable for priority is as follow:");
           printf("\npn\tbt\tat\tprio");
           for (int i = 0; i < n; i++)
           {
              printf("\n%d\t%d\t%d",process[i],burst_time[i],arrival_time[i],priority[i]);
           }
           calculation_priority(process,burst_time,n,arrival_time,priority);
        case 4:
           printf("\nExiting...");
           break;
       default:
         printf("\nInvalid choice");
        break;
       }
    } while (choice != 4);
    

}
void calculation(int process[],int burst_time[],int n,int arrival_time[]){
    int gt[100];
    int completion_time[100];
    int wt[100];
    int tt[100];
    float avg_waiting_time=0.0;
    float avg_turnaround_time=0.0;
    int waiting_time=0;
    int turnaround_time=0;
    for (int i = 0; i < n+1; i++)
    {
        gt[i+1] = gt[i] + burst_time[i];
    }
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            completion_time[i] = burst_time[i];
        }
        else
        {
            completion_time[i] = completion_time[i-1]  + burst_time[i];
        }
    }
    for (int i = 0; i < n; i++)
    {
        tt[i] = completion_time[i] - arrival_time[i];
    }
    for (int i = 0; i < n; i++)
    {
        wt[i] = tt[i] - burst_time[i]; 
    }
    for (int i = 0; i < n; i++)
    {
        waiting_time = waiting_time + wt[i];
        turnaround_time = turnaround_time + tt[i];
    }
    avg_turnaround_time = (float) turnaround_time/n;
    avg_waiting_time = (float) waiting_time/n;
    printf("\n the avgturnaround time : %f",avg_turnaround_time);
    printf("\nthe average waiting time :%f",avg_waiting_time);
    
    
}
void calculation_sjf(int process[],int burst_time[],int n,int arrival_time[]){
    int gt[100]={0};
    int tt[100];
    int wt[100];
    int completion_time[100]={0};
    int waiting_time=0;
    float average_waiting_time=0.0;
    float avg_turnaround_time=0.0;
    int turnaround_time=0;
    int temp1,temp2,temp3;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1 ; j++)
        {
            if (burst_time[j] > burst_time[j+1])
            {
                temp1=burst_time[j];
                burst_time[j] = burst_time[j+1];
                burst_time[j+1] = temp1;
                temp2 = arrival_time[j];
                arrival_time[j] = arrival_time[j+1];
                arrival_time[j+1] = temp2;
                temp3 = process[j];
                process[j] = process[j+1];
                process[j+1] = temp3;
           }
        }
    }
    for (int i = 0; i < n+1; i++)
    {
        gt[i+1] = gt[i]  + burst_time[i];
    }
    for (int i = 0; i < n; i++)
    {
        if (i==0)
        {
            completion_time[i] = burst_time[i];
        }
        else
        {
            completion_time[i] = completion_time[i-1] + burst_time[i];
        }
    }
    for (int i = 0; i < n; i++)
    {
        tt[i] = completion_time[i] - arrival_time[i];
    }
    for (int i = 0; i < n; i++)
    {
        wt[i] = tt[i] - burst_time[i];
    }
    for (int i = 0; i < n; i++)
    {
        waiting_time=waiting_time+wt[i];
        turnaround_time=turnaround_time+tt[i];
    }
    avg_turnaround_time=(float)turnaround_time/n;
    average_waiting_time=(float)waiting_time/n;
    printf("\nwaiting time:%f",average_waiting_time);
    printf("\nturnaround time:%f",avg_turnaround_time);
}
void calculation_priority(int process[],int burst_time[],int n,int arrival_time[],int priority[]){
      int gt[100];
      int wt[100];
      int tt[100];
      int completion_time[100];
      int waiting_time = 0;
      int turnaround_time = 0;
      float avg_turnaround_time= 0.0;
      float avg_waiting_time = 0.0;
      int temp1,temp2,temp3,temp4;
      for (int i = 0; i < n-1; i++)
      {
         for (int j = 0; j < n-i-1; j++)
         {
            if (priority[j] > priority[j+1])
            {
                temp1 = priority[j];
                priority[j] = priority[j+1];
                priority[j+1] = temp1;
                temp2 = burst_time[j];
                burst_time[j] = burst_time[j+1];
                burst_time[j+1] = temp2;
                temp3 = arrival_time[j];
                arrival_time[j] = arrival_time[j+1];
                arrival_time[j+1] = temp3;
                temp4 = process[j];
                process[j] = process[j+1];
                process[j+1] = temp4;
            }
         }
      }
      for (int i = 0; i < n+1; i++)
      {
        gt[i+1] = gt[i] + burst_time[i];
      }
      for (int i = 0; i < n; i++)
      {
         if (i == 0)
         {
             completion_time[i] = burst_time[i];
         }
         else
         {
            completion_time[i] = completion_time[i-1] + burst_time[i];
         }
      }
      for (int i = 0; i < n; i++)
      {
          tt[i] = completion_time[i] - arrival_time[i];
      }
      for (int i = 0; i < n; i++)
      {
         wt[i] =  tt[i] - burst_time[i];
      }
      for (int i = 0; i < n; i++)
      {
         waiting_time = waiting_time  + wt[i];
         turnaround_time = turnaround_time + tt[i];
      }
      avg_turnaround_time = (float) turnaround_time/n;
      avg_waiting_time = (float) waiting_time/n;
      printf("\nwaiting time:%f",avg_waiting_time);
      printf("\nturnaroun time:%f",avg_turnaround_time);
}