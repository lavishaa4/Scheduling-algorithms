#include <stdio.h>

int main() {
    int p_no[5] = {1,2,3,4,5};
    int a_t[5]  = {0,5,8,8,10};  // arrival times
    int b_t[5]  = {4,3,1,2,5};    // burst times
    int c_t[5]  = {0};            // completion times
    int t_a[5]  = {0};            // turnaround times
    int w_t[5]  = {0};            // waiting times
    int size = 5;

    int current_time = 0;

    for (int i = 0; i < size; ++i) {
        // If CPU is idle, advance time to arrival of next process
        if (current_time < a_t[i]) {
            current_time = a_t[i];
        }
        // process runs
        current_time += b_t[i];
        c_t[i] = current_time;
    }

    int sum_tat = 0;
    int sum_wt  = 0;

    printf("P_NO  AT  BT  CT  TAT  WT\n");
    for (int i = 0; i < size; ++i) {
        t_a[i] = c_t[i] - a_t[i];
        w_t[i] = t_a[i] - b_t[i];
        sum_tat += t_a[i];
        sum_wt  += w_t[i];
        printf("P%d    %2d   %d   %2d   %2d   %2d\n",
               p_no[i], a_t[i], b_t[i], c_t[i], t_a[i], w_t[i]);
    }

    double avg_tat = (double)sum_tat / size;
    double avg_wt  = (double)sum_wt  / size;

    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
    printf("Average Waiting Time    = %.2f\n", avg_wt);

    return 0;
}