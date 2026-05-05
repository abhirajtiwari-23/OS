#include <stdio.h>

#define MAX 10

int main() {
    int n, m; // n = processes, m = resources
    int alloc[MAX][MAX], request[MAX][MAX];
    int avail[MAX];
    int finish[MAX];
    int i, j, count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    // Initialize finish[]
    for(i = 0; i < n; i++) {
        int flag = 0;
        for(j = 0; j < m; j++) {
            if(alloc[i][j] != 0) {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
            finish[i] = 1; // no allocation → already finished
        else
            finish[i] = 0;
    }

    // Deadlock Detection Algorithm
    while(count < n) {
        int found = 0;

        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int possible = 1;

                for(j = 0; j < m; j++) {
                    if(request[i][j] > avail[j]) {
                        possible = 0;
                        break;
                    }
                }

                if(possible) {
                    for(j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];
                    }
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }

        if(found == 0)
            break;
    }

    // Check for deadlock
    int deadlock = 0;
    printf("\nProcesses in Deadlock: ");
    for(i = 0; i < n; i++) {
        if(finish[i] == 0) {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0)
        printf("None (No Deadlock)");

    printf("\n");

    return 0;
}

