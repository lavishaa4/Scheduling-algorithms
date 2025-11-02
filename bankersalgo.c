#include <stdio.h>

int main(void) {
    int n = 5; /* number of processes */
    int m = 3; /* number of resource types */

    /* Allocation matrix */
    int alloc[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    /* Max matrix */
    int max[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    /* Available vector */
    int avail[3] = {3, 3, 2};

    /* Need matrix = Max - Allocation */
    int need[5][3];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            need[i][j] = max[i][j] - alloc[i][j];

    /* Finish flags and safe sequence storage */
    int finish[5] = {0};
    int safeSeq[5];
    int count = 0;

    /* Attempt to find a safe sequence */
    while (count < n) {
        int found = 0; /* found a process in this pass? */
        for (int i = 0; i < n; ++i) {
            if (!finish[i]) {
                int canAllocate = 1;
                for (int j = 0; j < m; ++j) {
                    if (need[i][j] > avail[j]) {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate) {
                    /* Pretend to allocate and finish this process */
                    for (int j = 0; j < m; ++j)
                        avail[j] += alloc[i][j]; /* resources released after completion */
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) break; /* no further progress possible */
    }

    /* Check result and print */
    int allFinished = 1;
    for (int i = 0; i < n; ++i) {
        if (!finish[i]) { allFinished = 0; break; }
    }

    if (allFinished) {
        printf("The system is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < n; ++i) {
            /* print processes as P1..Pn */
            if (i > 0) printf(" -> ");
            printf("P%d", safeSeq[i] + 1);
        }
        printf("\n");
    } else {
        printf("The system is NOT in a safe state.\n");
    }

    return 0;
}