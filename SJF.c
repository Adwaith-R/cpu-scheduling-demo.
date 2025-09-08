#include <stdio.h>
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int completed;
};
int main() {
    int n, i, completed = 0, currentTime = 0, minIndex;
    float avgWT = 0, avgTAT = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    int ganttOrder[n], ganttStart[n], ganttEnd[n], gcCount = 0;
    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time of P%d: ", p[i].id);
        scanf("%d", &p[i].arrivalTime);
        printf("Enter Burst Time of P%d: ", p[i].id);
        scanf("%d", &p[i].burstTime);
        p[i].completed = 0;
    }
    while (completed < n) {
        minIndex = -1;
        int minBT = 1e9;
        for (i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && !p[i].completed) {
                if (p[i].burstTime < minBT) {
                    minBT = p[i].burstTime;
                    minIndex = i;
                }
            }
        }
        if (minIndex == -1) {
            currentTime++;
        } else {
            ganttOrder[gcCount] = p[minIndex].id;
            ganttStart[gcCount] = currentTime;
            currentTime += p[minIndex].burstTime;
            ganttEnd[gcCount] = currentTime;
            gcCount++;
            p[minIndex].turnaroundTime = currentTime - p[minIndex].arrivalTime;
            p[minIndex].waitingTime = p[minIndex].turnaroundTime - p[minIndex].burstTime;
            p[minIndex].completed = 1;
            completed++;
            avgWT += p[minIndex].waitingTime;
            avgTAT += p[minIndex].turnaroundTime;
        }
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].arrivalTime,
               p[i].burstTime,
               p[i].waitingTime,
               p[i].turnaroundTime);
    }
    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);

    printf("\nGantt Chart:\n");
    for (i = 0; i < gcCount; i++) {
        printf(" ");
        for (int j = ganttStart[i]; j < ganttEnd[i]; j++) printf("--");
    }
    printf("\n|");
    for (i = 0; i < gcCount; i++) {
        int space = (ganttEnd[i] - ganttStart[i]);
        for (int j = 0; j < space - 1; j++) printf(" ");
        printf("P%d", ganttOrder[i]);
        for (int j = 0; j < space - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    for (i = 0; i < gcCount; i++) {
        for (int j = ganttStart[i]; j < ganttEnd[i]; j++) printf("--");
    }
    printf("\n");
    for (i = 0; i < gcCount; i++) {
        printf("%d", ganttStart[i]);
        int space = (ganttEnd[i] - ganttStart[i]) * 2;
        for (int j = 0; j < space - 1; j++) printf(" ");
    }
    printf("%d\n", ganttEnd[gcCount - 1]);
    return 0;
}

