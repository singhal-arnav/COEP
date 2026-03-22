#include <stdio.h>

struct Activity {
    int start;
    int finish;
};

int main() {
    int n;
    printf("Enter number of activities: ");
    scanf("%d", &n);

    struct Activity activities[n];

    for (int i = 0; i < n; i++) {
        printf("Enter start time: ");
        scanf("%d", &activities[i].start);
        printf("Enter finish time: ");
        scanf("%d", &activities[i].finish);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (activities[j].finish > activities[j + 1].finish) {
                struct Activity temp = activities[j];
                activities[j] = activities[j + 1];
                activities[j + 1] = temp;
            }
        }
    }

    int count = 0;
    int lastFinish = -1;

    printf("Selected activities:\n");

    for (int i = 0; i < n; i++) {
        if (activities[i].start >= lastFinish) {
            printf("Start: %d Finish: %d\n", activities[i].start, activities[i].finish);
            lastFinish = activities[i].finish;
            count++;
        }
    }

    printf("Total activities selected: %d\n", count);

    return 0;
}
