#include <stdio.h>
#include <limits.h>

int n;
int cost[20][20];
int assigned[20];
int minCost = INT_MAX;

void branchAndBound(int worker, int currentCost) {
    if(worker == n) {
        if(currentCost < minCost)
            minCost = currentCost;
        return;
    }

    if(currentCost >= minCost)
        return;

    for(int j = 0; j < n; j++) {
        if(!assigned[j]) {
            assigned[j] = 1;
            branchAndBound(worker + 1, currentCost + cost[worker][j]);
            assigned[j] = 0;
        }
    }
}

int main() {
    printf("Enter number of employees/tasks: ");
    scanf("%d", &n);

    printf("Enter cost matrix:\n");

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    for(int i = 0; i < n; i++)
        assigned[i] = 0;

    branchAndBound(0, 0);

    printf("Minimum cost: %d\n", minCost);

    return 0;
}

