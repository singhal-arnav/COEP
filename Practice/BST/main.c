#include <stdio.h>
#include "bst.h"

int main() {
    BST t;

    init(&t);

    insert(&t, 2);
    insert(&t, 10);
    insert(&t, 11);
    preorder(t);
    printf("\n");
    postorder(t);
    printf("\n");
    inorder(t);

    return 0;
}