#include <stdio.h>

struct Processes {
    int ID, AT, BT, CT, TAT, WT, RT;
};

int main() {
    int n;
    printf("Enter no of processes: ");
    scanf("%d", &n);

    struct Processes p[n];
    for(int i=0; i<n; i++) {
        p[i].ID = i+1;
        printf("Arrival time: ");scanf("%d", &p[i].AT);
        printf("Burst time: ");scanf("%d", &p[i].BT);
        printf("\n");
    }

    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(p[j].AT > p[j+1].AT) {
                struct Processes temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int time_passed = 0;
    int sum_TAT = 0, sum_WT = 0, sum_RT = 0;

    for(int i=0; i<n; i++) {
        if(time_passed < p[i].AT) {
            time_passed = p[i].AT;
        }
        p[i].CT = time_passed + p[i].BT;
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
        p[i].RT = p[i].WT;

        time_passed = p[i].CT;
        sum_TAT += p[i].TAT;
        sum_WT += p[i].WT;
        sum_RT += p[i].RT;
    }

    printf("ID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].ID, p[i].AT, p[i].BT, p[i].CT,
               p[i].TAT, p[i].WT, p[i].RT);
    }
    printf("\n");
    printf("avg TAT: %.2f\n", (float)sum_TAT/n);
    printf("avg WT: %.2f\n", (float)sum_WT/n);
    printf("avg RT: %.2f\n", (float)sum_RT/n);

    return 0;
}
