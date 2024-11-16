typedef struct array {
    int *A;
    int size;
    int len;
}array;

void init(array *ap);
void append(array *ap, int val);
void traverse(array a);
void mov_freq(array *ap);