#include <stdio.h>
#include "dll.c"

int main() {
    DLL L1;

    init_DLL(&L1);

    insert_beg(&L1, 2);
    insert_beg(&L1, 10);
    insert_beg(&L1, -16);
    
    insert_end(&L1, 2);
    insert_end(&L1, 15);
    insert_end(&L1, 100);
    
    displayLR(L1);

    insert_pos(&L1, 2, 1000);

    displayRL(L1);

    if(is_palindrome(L1))
        printf("The list is a palindrome\n");
    else
        printf("The list is not a palindrome\n");

    remove_beg(&L1);
    
    displayLR(L1);

    remove_end(&L1);

    displayRL(L1);

    remove_pos(&L1, 1);

    displayLR(L1);

    return 0;
}