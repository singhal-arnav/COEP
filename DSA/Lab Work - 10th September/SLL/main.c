#include "SLL.c"

int main() {
    SLL L1;

    init_SLL(&L1);

    append(&L1, 3);
    append(&L1, 5);
    append(&L1, 20);

    printf("Contents of list:\n");
    traverse(L1);

    insert_at_beg(&L1, 10);
    
    remove_at_pos(&L1, 2);

    printf("New contents of list:\n");
    traverse(L1);
    
    printf("Length of the list = %d\n", len(L1));

    return 0;
}