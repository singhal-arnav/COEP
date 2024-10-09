typedef struct array{
	int* A;
	int size;
	int len;
}array;

void init(array* a, int size);
int is_empty(array* a);
int is_full(array* a);
void append(array* a, int data);
void insert_at_index(array* a, int idx, int data);
void remove_at_index(array* a, int idx);
void display(array* a);
int max(array* a);
int min(array* a);
void reverse(array* a);
void merge(array* a1, array* a2, array* res);