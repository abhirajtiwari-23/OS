#include <stdio.h>

#define MAX 10

typedef struct {
    int id, bt, deadline, period;
    int ct, wt, tat;
    int done;
} Process;

Process p[MAX];
int n;
void edf() {
    Process temp[MAX];

    for (int i = 0; i < n; i++) {
        temp[i] = p[i];
        temp[i].done = 0;
    }

    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int min_deadline = 9999;

        for (int i = 0; i < n; i++) {
            if (!temp[i].done && temp[i].deadline < min_deadline) {
                min_deadline = temp[i].deadline;
                idx = i;
            }
        }

        time += temp[idx].bt;
        temp[idx].ct = time;
        temp[idx].tat = temp[idx].ct;
        temp[idx].wt = temp[idx].tat - temp[idx].bt;
        temp[idx].done = 1;
        completed++;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (temp[i].deadline > temp[j].deadline) {
                Process t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    printf("\n===== Earliest Deadline First (EDF) Scheduling =====\n");
    printf("ID\tBT\tDeadline\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n",
               temp[i].id, temp[i].bt, temp[i].deadline,
               temp[i].ct, temp[i].wt, temp[i].tat);
    }
}
void rms() {
    Process temp[MAX];

    for (int i = 0; i < n; i++) {
        temp[i] = p[i];
        temp[i].done = 0;
    }

    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int min_period = 9999;

        for (int i = 0; i < n; i++) {
            if (!temp[i].done && temp[i].period < min_period) {
                min_period = temp[i].period;
                idx = i;
            }
        }

        time += temp[idx].bt;
        temp[idx].ct = time;
        temp[idx].tat = temp[idx].ct;
        temp[idx].wt = temp[idx].tat - temp[idx].bt;
        temp[idx].done = 1;
        completed++;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (temp[i].period > temp[j].period) {
                Process t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");
    printf("ID\tBT\tPeriod\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               temp[i].id, temp[i].bt, temp[i].period,
               temp[i].ct, temp[i].wt, temp[i].tat);
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details:\n");

    for (int i = 0; i < n; i++) {
        p[i].id = i;

        printf("\nProcess %d:\n", i);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);

        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);
    }
    edf();
    rms();

    return 0;
}
