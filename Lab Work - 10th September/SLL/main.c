#include "SLL.c"

int main() {
    SLL list;

    init_SLL(&list);

    append(&list, 3);
    append(&list, 5);
    append(&list, 20);

    printf("Contents of list:\n");
    traverse(list);

    insert_at_beg(&list, 10);
    
    remove_at_pos(&list, 2);

    printf("New contents of list:\n");
    traverse(list);
    
    printf("Length of the list = %d\n", len(list));

    return 0;
}