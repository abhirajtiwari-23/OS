#include <stdio.h>
#include <stdlib.h>

struct Process {
int id, at, bt, remaining_bt, ct, tat, wt, rt, started;
};

int main() {
int n, tq;
printf("Enter number of processes: ");
scanf("%d", &n);
printf("Enter Time Quantum: ");
scanf("%d", &tq);

struct Process p[n];
int queue[1000], front = 0, rear = 0, visited[100] = {0};
int queue_history[1000], h_idx = 0;

for (int i = 0; i < n; i++) {
    p[i].id = i + 1;
    printf("P%d - Arrival Time, Burst Time: ", i + 1);
    scanf("%d %d", &p[i].at, &p[i].bt);
    p[i].remaining_bt = p[i].bt;
    p[i].started = 0;
}

int cur_time = 0, completed = 0;
int gantt_p[500], gantt_t[500], g_idx = 0;


while (completed != n) {

    for (int i = 0; i < n; i++) {
        if (!visited[i] && p[i].at <= cur_time) {
            queue[rear++] = i;
            queue_history[h_idx++] = p[i].id;
            visited[i] = 1;
        }
    }

    if (front == rear) {

        if (g_idx == 0 || gantt_p[g_idx - 1] != -1) {
            gantt_p[g_idx] = -1;
            gantt_t[g_idx++] = cur_time;
        }
        cur_time++;
        continue;
    }

    int idx = queue[front++];

    if (!p[idx].started) {
        p[idx].rt = cur_time - p[idx].at;
        p[idx].started = 1;
    }

    gantt_p[g_idx] = p[idx].id;
    gantt_t[g_idx++] = cur_time;

    int execute = (p[idx].remaining_bt > tq) ? tq : p[idx].remaining_bt;
    p[idx].remaining_bt -= execute;
    cur_time += execute;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && p[i].at <= cur_time) {
            queue[rear++] = i;
            queue_history[h_idx++] = p[i].id;
            visited[i] = 1;
        }
    }

    if (p[idx].remaining_bt > 0) {
        queue[rear++] = idx;
        queue_history[h_idx++] = p[idx].id;
    } else {
        p[idx].ct = cur_time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        completed++;
    }
}
gantt_t[g_idx] = cur_time;

printf("\nID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
float s_ct=0, s_tat=0, s_wt=0, s_rt=0;
for (int i = 0; i < n; i++) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    s_ct += p[i].ct; s_tat += p[i].tat; s_wt += p[i].wt; s_rt += p[i].rt;
}

printf("\nReady Queue (Order of Entry/Re-entry):\n");
for (int i = 0; i < h_idx; i++) printf("+-----");
printf("+\n");
for (int i = 0; i < h_idx; i++) printf("| P%-2d ", queue_history[i]);
printf("|\n");
for (int i = 0; i < h_idx; i++) printf("+-----");
printf("+\n");
printf("\nGantt Chart:\n");
for (int i = 0; i < g_idx; i++) printf("+-----");
printf("+\n");
for (int i = 0; i < g_idx; i++) {
    if (gantt_p[i] == -1) printf("| IDL ");
    else printf("| P%-2d ", gantt_p[i]);
}
printf("|\n");
for (int i = 0; i < g_idx; i++) printf("+-----");
printf("+\n");
for (int i = 0; i <= g_idx; i++) {
    printf("%-6d", gantt_t[i]);
}

printf("\n\nAverage Metrics:\n");
printf("Avg CT: %.2f | Avg TAT: %.2f | Avg WT: %.2f | Avg RT: %.2f\n", s_ct/n, s_tat/n, s_wt/n, s_rt/n);

return 0;
}
