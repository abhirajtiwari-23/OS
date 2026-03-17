#include <stdio.h>
#include <stdbool.h>

struct Process {
int id, at, bt, priority, ct, tat, wt, rt, st;
bool completed;
};

int main() {
int n;
printf("Enter number of processes: ");
scanf("%d", &n);
struct Process p[n];

for(int i=0; i<n; i++) {
    p[i].id = i+1;
    printf("P%d - AT, BT, Priority: ", i+1);
    scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
    p[i].completed = false;
}

int completed = 0, cur_time = 0;
float total_ct=0, total_tat=0, total_wt=0, total_rt=0;
int gantt_p[100], gantt_t[100], g_idx = 0;

while(completed != n) {
    int idx = -1;
    int max_priority = 1e9;
    for(int i=0; i<n; i++) {
        if(p[i].at <= cur_time && !p[i].completed) {
            if(p[i].priority < max_priority) {
                max_priority = p[i].priority;
                idx = i;
            }
        }
    }

    if(idx != -1) {
        p[idx].st = cur_time;
        p[idx].ct = p[idx].st + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].rt = p[idx].st - p[idx].at;

        total_ct += p[idx].ct; total_tat += p[idx].tat;
        total_wt += p[idx].wt; total_rt += p[idx].rt;

        gantt_p[g_idx] = p[idx].id;
        gantt_t[g_idx++] = cur_time;
        cur_time = p[idx].ct;
        p[idx].completed = true;
        completed++;
    } else {
        cur_time++;
    }
}
gantt_t[g_idx] = cur_time;

printf("\nID\tAT\tBT\tPrio\tCT\tTAT\tWT\tRT\n");
for(int i=0; i<n; i++)
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt, p[i].rt);

printf("\nGantt Chart:\n");
for(int i=0; i<g_idx; i++) printf("+-----");
printf("+\n");
for(int i=0; i<g_idx; i++) printf("| P%-2d ", gantt_p[i]);
printf("|\n");
for(int i=0; i<g_idx; i++) printf("+-----");
printf("+\n");
for(int i=0; i<=g_idx; i++) printf("%-6d", gantt_t[i]);

printf("\n\nAvg CT: %.2f | Avg TAT: %.2f | Avg WT: %.2f | Avg RT: %.2f\n", total_ct/n, total_tat/n, total_wt/n, total_rt/n);
return 0;
}
