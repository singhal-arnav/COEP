#define N 10

typedef struct {
    int numVertices;
    int adjMat[N][N];
}graph;

void initGraph(graph *g, int V);
void insertEdge(graph *g, int n1, int n2);