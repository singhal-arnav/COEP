#include "graph.h"

void initGraph(graph *g, int V) {
    g -> numVertices = V;
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            g -> adjMat[i][j] = 0;
        }
    }
    return;
}

void insertEdge(graph *g, int n1, int n2) {
    g -> adjMat[n1][n2] = 1;
    g -> adjMat[n1][n2] = 1;
    return;
}