#include <stdio.h>

struct Job {
    int id;
    int deadline;
    int profit;
};

int main() {
    int n;
    printf("Enter number of jobs: ");
    scanf("%d", &n);

    struct Job jobs[n];

    for (int i = 0; i < n; i++) {
        printf("Enter job ID: ");
        scanf("%d", &jobs[i].id);
        printf("Enter deadline: ");
        scanf("%d", &jobs[i].deadline);
        printf("Enter profit: ");
        scanf("%d", &jobs[i].profit);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (jobs[j].profit < jobs[j + 1].profit) {
                struct Job temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }

    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }

    int slots[maxDeadline + 1];
    for (int i = 1; i <= maxDeadline; i++)
        slots[i] = -1;

    int totalProfit = 0;

    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline; j >= 1; j--) {
            if (slots[j] == -1) {
                slots[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    printf("Scheduled jobs: ");
    for (int i = 1; i <= maxDeadline; i++) {
        if (slots[i] != -1)
            printf("%d ", slots[i]);
    }

    printf("\nTotal profit: %d\n", totalProfit);

    return 0;
}
