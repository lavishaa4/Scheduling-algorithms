#include <stdio.h>

struct process {
    int p_no, a_t, b_t, p_t, c_t, t_a, w_t;
};

// Function to partition for quicksort (sort by priority)
int partition(struct process p[], int i, int j) {
    int last = p[j].p_t;
    int front = i - 1;
    for (int k = i; k < j; k++) {
        if (p[k].p_t < last) {  // smaller priority = higher priority
            front++;
            struct process temp = p[front];
            p[front] = p[k];
            p[k] = temp;
        }
    }
    struct process temp = p[front + 1];
    p[front + 1] = p[j];
    p[j] = temp;
    return front + 1;
}

void quickSort(struct process p[], int i, int j) {
    if (i < j) {
        int value = partition(p, i, j);
        quickSort(p, i, value - 1);
        quickSort(p, value + 1, j);
    }
}

int main() {
    struct process p[5] = {
        {1, 0, 4, 1, 0, 0, 0},
        {2, 0, 4, 5, 0, 0, 0},
        {3, 0, 1, 3, 0, 0, 0},
        {4, 0, 1, 2, 0, 0, 0},
        {5, 0, 5, 4, 0, 0, 0}
    };

    int size = sizeof(p) / sizeof(struct process);
    quickSort(p, 0, size - 1);

    int time = 0;
    for (int i = 0; i < size; i++) {
        time += p[i].b_t;
        p[i].c_t = time;
        p[i].t_a = p[i].c_t - p[i].a_t;
        p[i].w_t = p[i].t_a - p[i].b_t;
    }

    printf("P_NO\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < size; i++) {
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].p_no, p[i].a_t, p[i].b_t, p[i].p_t,
               p[i].c_t, p[i].t_a, p[i].w_t);
    }

    // Average times
    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < size; i++) {
        avg_tat += p[i].t_a;
        avg_wt += p[i].w_t;
    }
    avg_tat /= size;
    avg_wt /= size;

    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
    printf("Average Waiting Time    = %.2f\n", avg_wt);

    return 0;
}
