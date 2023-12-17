#include <stdio.h>
#include <limits.h>

#define size 100

void calculation(int burst_time[], int priority[], int process[], int n);
int main() {
    int burst_time[size];
    int priority[size];
    int process[size];
    int n;

    printf("\tWELCOME TO PRIORITY PREEMPTIVE CALCULATOR\t \n");
    printf("\nEnter the number of processes:\n");
    scanf("%d", &n);

    printf("\nEnter the process number for each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &process[i]);
    }

    printf("\nEnter the burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &burst_time[i]);
    }

    printf("\nEnter the priority for each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &priority[i]);
    }

    printf("\nThe table for Priority Preemptive is as follows:\n");
    printf("pn \t bt \t pr\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", process[i], burst_time[i], priority[i]);
    }

    calculation(burst_time, priority, process, n);

    return 0;
}

void calculation(int burst_time[], int priority[], int process[], int n) {
    int wt[size] = {0};
    int tt[size] = {0};
    int completion_time[size] = {0};
    int waiting_time = 0;
    float avg_waiting_time = 0.0;
    int turnaround_time = 0;
    float avg_turnaround_time = 0.0;
    int current_time = 0;
    int completed = 0;
    int remaining_time[size];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }

    while (completed < n) {
        int highest_priority = INT_MAX;
        int highest_process = -1;

        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0 && priority[i] < highest_priority && current_time >= priority[i]) {
                highest_priority = priority[i];
                highest_process = i;
            }
        }

        if (highest_process == -1) {
            current_time++;
        } else {
            remaining_time[highest_process]--;
            if (remaining_time[highest_process] == 0) {
                completed++;
                int end_time = current_time + 1;
                tt[highest_process] = end_time;
                wt[highest_process] = tt[highest_process] - burst_time[highest_process];
                waiting_time += wt[highest_process];
                current_time = end_time;
                completion_time[highest_process] = end_time;
                turnaround_time += tt[highest_process];
            } else {
                current_time++;
            }
        }
    }

    printf("\nThe Table for Priority Preemptive is as follows:\n");
    printf("pn \t bt \t pr \t wt \t tt \t ct \n");
    for (int i = 0; i < n; i++) {
        printf("%d \t %d \t %d \t %d \t %d \t %d \n", process[i], burst_time[i], priority[i], wt[i], tt[i], completion_time[i]);
    }

    avg_turnaround_time = (float)turnaround_time / n;
    avg_waiting_time = (float)waiting_time / n;

    printf("\nThe Average waiting time is: %f", avg_waiting_time);
    printf("\nThe Average turnaround time is: %f", avg_turnaround_time);
}
