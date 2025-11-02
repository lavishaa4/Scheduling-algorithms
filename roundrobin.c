#include <stdio.h>
#include <stdbool.h>

struct process {
    int p_no, a_t, b_t, c_t, t_a, w_t;
};

int main(void) {
    int n = 5, tq = 2;
    struct process p[5] = {
        {1, 0, 4, 0, 0, 0},
        {2, 0, 4, 0, 0, 0},
        {3, 0, 1, 0, 0, 0},
        {4, 0, 1, 0, 0, 0},
        {5, 0, 5, 0, 0, 0}
    };

    int rem_bt[5];
    for (int i = 0; i < n; i++) {
        rem_bt[i] = p[i].b_t;
    }

    int time = 0;
    bool done;

    /* Round Robin simulation */
    while (1) {
        done = true;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = false;
                if (rem_bt[i] > tq) {
                    /* execute for time quantum */
                    time += tq;
                    rem_bt[i] -= tq;
                } else {
                    /* finish this process */
                    time += rem_bt[i];
                    p[i].c_t = time;
                    rem_bt[i] = 0;
                }
            }
        }
        if (done) {
            break;
        }
    }

    /* compute TAT and WT and sums */
    int sum_tat = 0, sum_wt = 0;
    for (int i = 0; i < n; i++) {
        p[i].t_a = p[i].c_t - p[i].a_t;
        p[i].w_t = p[i].t_a - p[i].b_t;
        sum_tat += p[i].t_a;
        sum_wt += p[i].w_t;
    }

    /* print results */
    printf("P_NO\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\n",
               p[i].p_no, p[i].a_t, p[i].b_t, p[i].c_t, p[i].t_a, p[i].w_t);
    }

    printf("\nAverage Turnaround Time = %.2f\n", (double)sum_tat / n);
    printf("Average Waiting Time    = %.2f\n", (double)sum_wt / n);

    return 0;
}
