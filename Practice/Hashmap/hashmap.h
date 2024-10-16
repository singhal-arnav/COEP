#define MAX_TABLE_SIZE 100

typedef struct element {
    char *key, *value; // key is the URL itself, value could be metadata or timestamp
}element;

typedef element hashmap[MAX_TABLE_SIZE];

void init_table(hashmap h);
int transform(char *key);
int hash(char *key);
void linear_insert(element item, hashmap h);