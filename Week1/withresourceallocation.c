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

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    // -------- RESOURCE REQUEST PART --------
    int process;
    printf("Enter process number making request (0 to %d): ", n - 1);
    scanf("%d", &process);

    int Request[m];
    printf("Enter request vector:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &Request[j]);

    // Check Request <= Need
    for (int j = 0; j < m; j++) {
        if (Request[j] > Need[process][j]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return 0;
        }
    }

    // Check Request <= Available
    for (int j = 0; j < m; j++) {
        if (Request[j] > Available[j]) {
            printf("Resources not available. Process must wait.\n");
            return 0;
        }
    }

    // Pretend allocation
    for (int j = 0; j < m; j++) {
        Available[j] -= Request[j];
        Allocation[process][j] += Request[j];
        Need[process][j] -= Request[j];
    }

    // -------- SAFETY ALGORITHM --------
    for (int j = 0; j < m; j++)
        Work[j] = Available[j];

    for (int i = 0; i < n; i++)
        Finish[i] = 0;

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

                    SafeSequence[count++] = i;
                    Finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("Request cannot be granted. System is UNSAFE.\n");
            return 0;
        }
    }

    printf("Request can be granted. System is SAFE.\n");
    printf("Safe Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d", SafeSequence[i]);
        if (i != n - 1) printf(" -> ");
    }
    printf("\n");

    return 0;
}


