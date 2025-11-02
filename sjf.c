#include <stdio.h>

struct process {
    int p_no, a_t, b_t, c_t, t_a, w_t;
};

int main() {
    int n = 5;
    struct process p[5] = {
        {1, 0, 4, 0, 0, 0},
        {2, 0, 4, 0, 0, 0},
        {3, 0, 1, 0, 0, 0},
        {4, 0, 1, 0, 0, 0},
        {5, 0, 5, 0, 0, 0}
    };

    // Sort by Burst Time (Shortest Job First)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].b_t > p[j + 1].b_t) {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Calculate CT, TAT, WT
    int time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].b_t;
        p[i].c_t = time;
        p[i].t_a = p[i].c_t - p[i].a_t;
        p[i].w_t = p[i].t_a - p[i].b_t;
    }

    // Print results
    printf("P_NO\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\n",
               p[i].p_no, p[i].a_t, p[i].b_t,
               p[i].c_t, p[i].t_a, p[i].w_t);
    }

    // Average times
    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        avg_tat += p[i].t_a;
        avg_wt += p[i].w_t;
    }
    avg_tat /= n;
    avg_wt /= n;

    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
    printf("Average Waiting Time    = %.2f\n", avg_wt);

    return 0;
}