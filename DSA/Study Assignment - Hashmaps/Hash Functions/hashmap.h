typedef struct entry {
    int key;
    int value;
} entry;

typedef struct hashmap {
    entry* table;
    int size;
} hashmap;

void init_hashmap(hashmap *hp, int size);
int division_hash(int key, int size);
int multiplication_hash(int key, int size);
int universal_hash(int key, int size, int a, int b, int p);
void division_insert(hashmap *hp, int key, int value);
void multiplication_insert(hashmap *hp, int key, int value);
void universal_insert(hashmap *hp, int key, int value);