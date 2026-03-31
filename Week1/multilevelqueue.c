#include <stdio.h>

struct Process {
    int pid, at, bt;
    int wt, tat, ct;
    int type;
    int completed;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[50];

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("PID: ");
        scanf("%d", &p[i].pid);

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);

        p[i].completed = 0;
    }

    int time = 0, completed = 0;

    int gantt_pid[100], gantt_time[100];
    int g = 0;

    while (completed < n) {
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time && p[i].type == 0) {
                if (idx == -1 || p[i].at < p[idx].at)
                    idx = i;
            }
        }

        if (idx == -1) {
            for (int i = 0; i < n; i++) {
                if (!p[i].completed && p[i].at <= time && p[i].type == 1) {
                    if (idx == -1 || p[i].at < p[idx].at)
                        idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        if (time < p[idx].at)
            time = p[idx].at;


        gantt_pid[g] = p[idx].pid;
        gantt_time[g] = time;
        g++;


        p[idx].wt = time - p[idx].at;
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].completed = 1;

        completed++;
    }

    gantt_time[g] = time;


    float total_wt = 0, total_tat = 0;

    printf("\nPID\tAT\tBT\tWT\tTAT\tCT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].wt, p[i].tat, p[i].ct);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);


    printf("\nGantt Chart:\n|");
    for (int i = 0; i < g; i++) {
        printf(" P%d |", gantt_pid[i]);
    }

    printf("\n%d", gantt_time[0]);
    for (int i = 1; i <= g; i++) {
        printf(" %d", gantt_time[i]);
    }

    printf("\n");

    return 0;
}
