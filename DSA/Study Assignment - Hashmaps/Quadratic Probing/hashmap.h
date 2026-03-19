typedef struct entry {
    int key;
    int value;
} entry;

typedef struct hashmap {
    entry* table;
    int size;
} hashmap;

void init_hashmap(hashmap *hp, int size);
int hash(int key, int size);
void insert(hashmap *hp, int key, int value);
