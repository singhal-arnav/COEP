#include "ascii.c"

int main() {
    ASCII L1;

    init_ASCII(&L1); //initializes the list
    ASCII_of(&L1, 'z'); //stores digits of ascii code in dll, here it stores {6, 5}

    printf("Contents of list: ");
    traverse(L1); //traverses the list and prints value of each node
    Destroy(&L1); //destroys the list

    traverse(L1); //does not display anything as all nodes have been freed

    return 0;
}