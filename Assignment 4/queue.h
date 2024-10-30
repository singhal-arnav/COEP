typedef struct data {
    char name[16];
    unsigned int age;
}data;

typedef struct node {
    data data;
    struct node *next;
}node;

typedef struct queue {
    node *head, *tail;
}queue;

void qinit(queue *qp);
void enq(queue *qp, data d);
data deq(queue *qp);
int qfull(queue *qp);
int qempty(queue *qp);