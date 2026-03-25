#include <stdio.h>
#include <limits.h>

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

int main() {
    int e, f;

    printf("Enter number of eggs: ");
    scanf("%d", &e);

    printf("Enter number of floors: ");
    scanf("%d", &f);

    int dp[e+1][f+1];

    for(int i = 1; i <= e; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }

    for(int j = 1; j <= f; j++)
        dp[1][j] = j;

    for(int i = 2; i <= e; i++) {
        for(int j = 2; j <= f; j++) {
            dp[i][j] = INT_MAX;

            for(int x = 1; x <= j; x++) {
                int res = 1 + max(dp[i-1][x-1], dp[i][j-x]);
                dp[i][j] = min(dp[i][j], res);
            }
        }
    }

    printf("Minimum number of trials: %d\n", dp[e][f]);

    return 0;
}
