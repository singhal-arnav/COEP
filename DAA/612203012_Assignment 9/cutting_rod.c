#include <stdio.h>

#define max(a,b) ((a) > (b) ? (a) : (b))

int main() {
    int n;

    printf("Enter length of rod: ");
    scanf("%d", &n);

    int price[n+1];

    for(int i = 1; i <= n; i++) {
        printf("Enter price for length %d: ", i);
        scanf("%d", &price[i]);
    }

    int dp[n+1];
    int cut[n+1];

    dp[0] = 0;

    for(int i = 1; i <= n; i++) {
        dp[i] = 0;
        cut[i] = 0;

        for(int j = 1; j <= i; j++) {
            if(price[j] + dp[i - j] > dp[i]) {
                dp[i] = price[j] + dp[i - j];
                cut[i] = j;
            }
        }
    }

    printf("Maximum obtainable value: %d\n", dp[n]);

    printf("Selected lengths (backtracked): ");
    int len = n;
    while (len > 0) {
        for (int j = 1; j <= len; j++) {
            if (dp[len] == price[j] + dp[len - j]) {
                printf("%d ", j);
                len -= j;
                break;
            }
        }
    }

    printf("\n");

    return 0;
}
