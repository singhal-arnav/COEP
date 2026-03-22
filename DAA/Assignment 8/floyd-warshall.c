#include <stdio.h>
#include <limits.h>

#define INF INT_MAX

void printPath(int n, int pred[n+1][n+1], int i, int j) {
    if(i == j) {
        printf("%d", i);
        return;
    }

    if(pred[i][j] == -1) {
        printf("No path");
        return;
    }

    printPath(n, pred, i, pred[i][j]);
    printf(" -> %d", j);
}

int main() {
    int n;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int dist[n+1][n+1];
    int pred[n+1][n+1];

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;

            pred[i][j] = -1;
        }
    }

    int edges;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    for(int i = 0; i < edges; i++) {
        int u, v, w;

        printf("\nEdge %d\n", i + 1);

        printf("Enter start node: ");
        scanf("%d", &u);

        printf("Enter end node: ");
        scanf("%d", &v);

        printf("Enter weight: ");
        scanf("%d", &w);

        dist[u][v] = w;
        pred[u][v] = u;
    }

    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = pred[k][j];
                }
            }
        }
    }

    printf("\nShortest paths between every pair:\n");

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i != j) {
                printf("%d-%d (Distance: ", i, j);

                if(dist[i][j] == INF) {
                    printf("INF): No path");
                } 
                else {
                    printf("%d): ", dist[i][j]);
                    printPath(n, pred, i, j);
                }

                printf("\n");
            }
        }
    }

    return 0;
}
