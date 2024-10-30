#include <stdio.h>
#include "cll.c"

int main() {
    CLL L1;

    init_CLL(&L1);

    insert_beg(&L1, 3);
    insert_beg(&L1, 4);

    /*insert_end(&L1, 5);
    insert_end(&L1, 6);

    display(L1);

    insert_pos(&L1, 2, 10);

    remove_beg(&L1);
    remove_end(&L1);*/

    display(L1);

    return 0;
}