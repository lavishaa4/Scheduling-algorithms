#include <stdio.h>

struct process {
    int p_no;     /* process id */
    int a_t;      /* arrival time (all 0 here) */
    int b_t;      /* burst time */
    int rem_bt;   /* remaining burst time (for RR) */
    int p_t;      /* priority value (lower => higher priority in this example) */
    int c_t;      /* completion time */
    int tat;      /* turnaround time */
    int wt;       /* waiting time */
};

int main(void) {
    /* Example processes (no input). All arrival times = 0 */
    int n = 5;
    int tq = 2; /* time quantum for high-priority RR */
    struct process all[5] = {
        {1, 0, 4, 4, 2, 0, 0, 0},
        {2, 0, 4, 4, 4, 0, 0, 0},
        {3, 0, 1, 1, 6, 0, 0, 0},
        {4, 0, 1, 1, 7, 0, 0, 0},
        {5, 0, 5, 5, 3, 0, 0, 0}
    };

    /* Split into HQ and LQ by priority threshold:
       p_t <= 5 -> HQ (higher priority)
       p_t >  5 -> LQ (lower priority)
       (change threshold as needed) */
    struct process hq[5], lq[5];
    int hc = 0, lc = 0;
    for (int i = 0; i < n; ++i) {
        if (all[i].p_t <= 5) hq[hc++] = all[i];
        else lq[lc++] = all[i];
    }

    int time = 0;

    /* --- High Priority: Round-Robin (tq) --- */
    if (hc > 0) {
        int done;
        while (1) {
            done = 1; /* assume done until we find a remaining job */
            for (int i = 0; i < hc; ++i) {
                if (hq[i].rem_bt > 0) {
                    done = 0;
                    int slice = (hq[i].rem_bt > tq) ? tq : hq[i].rem_bt;
                    time += slice;
                    hq[i].rem_bt -= slice;
                    if (hq[i].rem_bt == 0) {
                        hq[i].c_t = time;
                        hq[i].tat = hq[i].c_t - hq[i].a_t;
                        hq[i].wt  = hq[i].tat - hq[i].b_t;
                    }
                }
            }
            if (done) break;
        }
    }

    /* --- Low Priority: FCFS (execute in the order present in lq[]) --- */
    for (int i = 0; i < lc; ++i) {
        time += lq[i].b_t;
        lq[i].c_t = time;
        lq[i].tat = lq[i].c_t - lq[i].a_t;
        lq[i].wt  = lq[i].tat - lq[i].b_t;
    }

    /* Print summary and averages */
    printf("Process | Queue | CT  | TAT | WT\n");
    int sum_tat = 0, sum_wt = 0;
    for (int i = 0; i < hc; ++i) {
        printf("P%d      | HQ    | %3d | %3d | %2d\n",
               hq[i].p_no, hq[i].c_t, hq[i].tat, hq[i].wt);
        sum_tat += hq[i].tat;
        sum_wt  += hq[i].wt;
    }
    for (int i = 0; i < lc; ++i) {
        printf("P%d      | LQ    | %3d | %3d | %2d\n",
               lq[i].p_no, lq[i].c_t, lq[i].tat, lq[i].wt);
        sum_tat += lq[i].tat;
        sum_wt  += lq[i].wt;
    }

    double avg_tat = (double)sum_tat / n;
    double avg_wt  = (double)sum_wt  / n;

    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
    printf("Average Waiting Time    = %.2f\n", avg_wt);

    return 0;
}
