#include <stdio.h>
#include "dll.c"

int main() {
    DLL list;

    init_DLL(&list);

    insert_beg(&list, 2);
    insert_beg(&list, 10);
    insert_beg(&list, -16);
    
    insert_end(&list, 2);
    insert_end(&list, 15);
    insert_end(&list, 100);
    
    displayLR(list);

    insert_pos(&list, 2, 1000);

    displayRL(list);

    if(is_palindrome(list))
        printf("The list is a palindrome\n");
    else
        printf("The list is not a palindrome\n");

    remove_beg(&list);
    
    displayLR(list);

    remove_end(&list);

    displayRL(list);

    remove_pos(&list, 1);

    displayLR(list);

    return 0;
}