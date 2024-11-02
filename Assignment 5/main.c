#include <stdio.h>
#include "bst.c"

int main() {
    int choice, flag = 1;
    BST t;
    char month[10];

    while(flag) {
        printf("Enter 1 to initialize the tree\n");
        printf("Enter 2 to insert a node into the tree\n");
        printf("Enter 3 to remove a node from the tree\n");
        printf("Enter 4 to traverse the tree\n");
        printf("Enter 5 to destroy the tree\n");

        scanf("%d", &choice);

        switch(choice) {
            case 1:
                initBST(&t);
                break;
            case 2:
                printf("Enter the month to be inserted: ");
                scanf("%s", month);
                insertNode(&t, month);
                break;
            case 3:
                printf("Enter the month to be removed from the tree: ");
                scanf("%s", month);
                removeNode(&t, month);
                break;
            case 4:
                printf("Printing preorder traversal of the tree:\n");
                traverse(t);
                break;
            case 5:
                destroyTree(&t);
                printf("All nodes of the tree have been deleted.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
        printf("Enter 1 if you wish to continue or 0 if you wish to exit: ");
        scanf("%d", &flag);
    }

    return 0;
}