#include <stdio.h>

#define max(a,b) ((a) > (b) ? (a) : (b))

int main() {
    int n, W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    int weight[n], value[n];

    for(int i = 0; i < n; i++) {
        printf("Enter weight of item %d: ", i + 1);
        scanf("%d", &weight[i]);
        printf("Enter value of item %d: ", i + 1);
        scanf("%d", &value[i]);
    }

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    int dp[n + 1][W + 1];

    for(int i = 0; i <= n; i++) {
        for(int w = 0; w <= W; w++) {
            if(i == 0 || w == 0)
                dp[i][w] = 0;
            else if(weight[i - 1] <= w)
                dp[i][w] = max(value[i - 1] + dp[i - 1][w - weight[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    printf("Maximum value in knapsack: %d\n", dp[n][W]);

    int w = W;

    printf("Items selected: ");

    for(int i = n; i > 0 && w > 0; i--) {
        if(dp[i][w] != dp[i - 1][w]) {
            printf("%d ", i);
            w -= weight[i - 1];
        }
    }

    printf("\n");

    return 0;
}
