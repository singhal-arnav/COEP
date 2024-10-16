#include "hashmap.c"

int main() {
    hashmap h;

    init_table(h);

    element item = {"Arnav", "COEP"};
    element item2 = {"Arnav", "COEP"};

    linear_insert(item, h);
    linear_insert(item2, h);

    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
        printf("%s : %s\n", h[i].key, h[i].value);
    }

    return 0;
}