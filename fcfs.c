#include <stdio.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int start;
    int completion;
    int waiting;
    int turnaround;
};

void sortByArrival(struct Process p[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(p[i].arrival > p[j].arrival) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n = 4;
    struct Process p[n];

    // Hardcoded default values
    p[0].id = 1; p[0].arrival = 0; p[0].burst = 4;
    p[1].id = 2; p[1].arrival = 1; p[1].burst = 3;
    p[2].id = 3; p[2].arrival = 2; p[2].burst = 1;
    p[3].id = 4; p[3].arrival = 3; p[3].burst = 2;

    printf("--HELLO ADHITHYAN!--\n");
    printf("Default process data:\n");
    printf("Process\tArrival Time\tBurst Time\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\n", p[i].id, p[i].arrival, p[i].burst);
    }

    char choice;
    printf("\nDo you want to change the data? (y/n): ");
    scanf(" %c", &choice);

    if(choice == 'y' || choice == 'Y') {
        for(int i = 0; i < n; i++) {
            printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
            scanf("%d %d", &p[i].arrival, &p[i].burst);
            p[i].id = i + 1;
        }
    }

    // Sort processes by arrival time
    sortByArrival(p, n);

    int time = 0;
    int totalWaiting = 0;
    int totalTurnaround = 0;

    // Calculate scheduling details
    for(int i = 0; i < n; i++) {
        if(time < p[i].arrival) {
            time = p[i].arrival; // CPU idle until process arrives
        }
        p[i].start = time;
        p[i].completion = time + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].start - p[i].arrival;
        totalWaiting += p[i].waiting;
        totalTurnaround += p[i].turnaround;
        time = p[i].completion;
    }

    // Print detailed results
    printf("\n--- FCFS CPU Scheduling Details ---\n");
    printf("Process | Arrival | Burst | Start | Completion | Waiting | Turnaround\n");
    printf("---------------------------------------------------------------\n");
    for(int i = 0; i < n; i++) {
        printf(" P%-4d | %-7d | %-5d | %-5d | %-10d | %-7d | %-10d\n",
            p[i].id, p[i].arrival, p[i].burst, p[i].start, p[i].completion, p[i].waiting, p[i].turnaround);
    }
    printf("---------------------------------------------------------------\n");

    // Print average times
    printf("Average Waiting Time    : %.2f\n", (float)totalWaiting / n);
    printf("Average Turnaround Time : %.2f\n", (float)totalTurnaround / n);

    // Gantt Chart with idle times
    printf("\nGantt Chart:\n");

    // Top bar
    printf(" ");
    for(int i = 0; i < n; i++) {
        int idle = (i == 0) ? (p[i].start - 0) : (p[i].start - p[i-1].completion);
        if(idle > 0) {
            printf("   IDLE   ");
        }
        printf("  P%-4d  ", p[i].id);
    }
    printf("\n ");

    // Bottom bar
    for(int i = 0; i < n; i++) {
        int idle = (i == 0) ? (p[i].start - 0) : (p[i].start - p[i-1].completion);
        if(idle > 0) {
            printf("---------");
        }
        printf("---------");
    }
    printf("\n0");

    // Time markers
    for(int i = 0; i < n; i++) {
        int idle = (i == 0) ? (p[i].start - 0) : (p[i].start - p[i-1].completion);
        if(idle > 0) {
            printf("\t%d", p[i].start);
        }
        printf("\t%d", p[i].completion);
    }
    printf("\n");

    return 0;
}
