#include <stdio.h>

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int Allocation[n][m], Max[n][m], Need[n][m], Available[m];
    int Finish[n], SafeSequence[n];
    int Work[m];

    printf("Enter Allocation Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &Allocation[i][j]);

    printf("Enter Max Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &Max[i][j]);

    printf("Enter Available Resources (%d):\n", m);
    for (int j = 0; j < m; j++)
        scanf("%d", &Available[j]);

    for (int j = 0; j < m; j++)
        Work[j] = Available[j];

    for (int i = 0; i < n; i++)
        Finish[i] = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    int count = 0;

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (Finish[i] == 0) {
                int canRun = 1;
                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        canRun = 0;
                        break;
                    }
                }
                if (canRun) {
                    for (int j = 0; j < m; j++)
                        Work[j] += Allocation[i][j];

                    Finish[i] = 1;
                    SafeSequence[count++] = i;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is in an UNSAFE STATE (Potential Deadlock).\n");
            return 0;
        }
    }

    printf("System is in a SAFE STATE.\nSafe Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d", SafeSequence[i]);
        if (i != n - 1) printf(" -> ");
    }
    printf("\n");

    return 0;
}
