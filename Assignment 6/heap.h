typedef struct heap{
    int *h;
    int size;
    int rear;
}heap;

void init_heap(heap *h1, int size);
void insert_heap(heap *h1, int k);
int parent(int index);
void swaph(heap *h1, int a, int b);
void heapify(heap *h1); //Heapify from top to bottom
void print_heap(heap h1);
void heap_sort(heap *h1);
