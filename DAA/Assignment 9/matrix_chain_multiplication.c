#include <stdio.h>
#include <limits.h>

void print_optimal_seq(int n, int k_table[][n + 1], int i, int j) {
    if(i == j) {
        printf("A%d", i);
    }
    else {
        printf("(");
        print_optimal_seq(n, k_table, i, k_table[i][j]);
        print_optimal_seq(n, k_table, k_table[i][j] + 1, j);
        printf(")");
    }
}

int main() {
    int n;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int d[n+1];

    printf("Enter dimensions array:\n");
    for(int i = 0; i <= n; i++) {
        scanf("%d", &d[i]);
    }

    int m[n+1][n+1];
    int k_table[n+1][n+1];

    for(int i = 1; i <= n; i++)
        m[i][i] = 0;

    for(int len = 2; len <= n; len++) {
        for(int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            m[i][j] = INT_MAX;

            for(int k = i; k < j; k++) {
                int cost = m[i][k] + m[k+1][j] + d[i-1]*d[k]*d[j];

                if(cost < m[i][j]) {
                    m[i][j] = cost;
                    k_table[i][j] = k;
                }
            }
        }
    }

    printf("Minimum number of multiplications: %d\n\n", m[1][n]);

    printf("Cost Table:\n");
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i > j)
                printf("0 ");
            else
                printf("%d ", m[i][j]);
        }
        printf("\n");
    }

    printf("\nK Table:\n");
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i >= j)
                printf("0 ");
            else
                printf("%d ", k_table[i][j]);
        }
        printf("\n");
    }
    
    printf("Optimal multiplication sequence: ");
    print_optimal_seq(n, k_table, 1, n);
    printf("\n");

    return 0;
}
