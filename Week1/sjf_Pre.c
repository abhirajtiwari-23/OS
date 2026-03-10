#include <stdio.h>

struct Processes {
    int ID, AT, BT, CT, TAT, WT, RT;
    int remainingBT;
    int completed;
};

int main() {
    int n;
    printf("Enter no of processes: ");scanf("%d", &n);

    struct Processes p[n];

    for(int i=0;i<n;i++) {
        p[i].ID = i+1;
        printf("Arrival time: ");scanf("%d",&p[i].AT);
        printf("Burst time: ");scanf("%d",&p[i].BT);

        p[i].remainingBT = p[i].BT;
        p[i].completed = 0;
        p[i].RT = -1;
        printf("\n");
    }

    int time_passed = 0, completed = 0;
    int sum_TAT = 0, sum_WT = 0, sum_RT = 0;

    while(completed < n) {
        int idx = -1;
        int minBT = 1e9;

        for(int i=0;i<n;i++) {
            if(p[i].AT <= time_passed && !p[i].completed) {
                if(p[i].remainingBT < minBT) {
                    minBT = p[i].remainingBT;
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            time_passed++;
            continue;
        }

        if(p[idx].RT == -1){
            p[idx].RT = time_passed - p[idx].AT;
        }

        p[idx].remainingBT--;
        time_passed++;

        if(p[idx].remainingBT == 0) {
            p[idx].completed = 1;
            completed++;

            p[idx].CT = time_passed;
            p[idx].TAT = p[idx].CT - p[idx].AT;
            p[idx].WT = p[idx].TAT - p[idx].BT;

            sum_TAT += p[idx].TAT;
            sum_WT += p[idx].WT;
            sum_RT += p[idx].RT;
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i=0;i<n;i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].ID, p[i].AT, p[i].BT,
               p[i].CT, p[i].TAT, p[i].WT, p[i].RT);
    }

    printf("\nAverage TAT: %.2f\n", (float)sum_TAT/n);
    printf("Average WT: %.2f\n", (float)sum_WT/n);
    printf("Average RT: %.2f\n", (float)sum_RT/n);

    return 0;
}
