#include "array.c"
#include <limits.h>

int main()
{
    array a;
    int choice, val, ind, c = 1;
    
    while(c) {
        printf("Enter 1 to initialize the array\n");
        printf("Enter 2 to append an element to the array\n");
        printf("Enter 3 to insert an element at a particular index\n");
        printf("Enter 4 to remove the element at a particular index\n");
        printf("Enter 5 to display the elements of the array\n");
        printf("Enter 6 to display the maximum element of the array\n");
        printf("Enter 7 to display the minimum element of the array\n");
        printf("Enter 8 to merge two arrays\n");

        scanf("%d", &choice);

        switch(choice) {
            case 1:
                int size, len;
                printf("Enter the maximum size of the array: ");
                scanf("%d", &size);
                printf("Enter the number of elements to populate the array with: ");
                scanf("%d", &len);
                
                init(&a, size);
                for(int i = 0; i < len; i++)
                    append(&a, rand());
                
                break;
            case 2:
                printf("Enter the element to be appended to the array: ");
                scanf("%d", &val);
                append(&a, val);
                break;
            case 3:
                printf("Enter the value to be inserted into the array: ");
                scanf("%d", &val);
                printf("Enter the index at which the value is to be inserted: ");
                scanf("%d", &ind);
                insert_at_index(&a, ind, val);
                break;
            case 4:
                printf("Enter the index of the element which is to be removed: ");
                scanf("%d", &ind);
                remove_at_index(&a, ind);
                break;
            case 5:
                display(&a);
                break;
            case 6:
                printf("Maximum element of the array: %d", max(&a));
                break;
            case 7:
                printf("Minimum element of the array: %d", min(&a));
                break;
            case 8:
                array a1, a2, a3;
                
                init(&a1, 2);
                append(&a1, 1);
                append(&a1, 2);
                printf("First array: ");
                display(&a1);

                init(&a2, 2);
                append(&a2, 3);
                append(&a2, 4);
                printf("Second array: ");
                display(&a2);

                init(&a3, 4);
                merge(&a1, &a2, &a3);
                printf("Merged array: ");
                display(&a3);

                break;
            default:
                break;        
        }

        printf("Enter 1 to continue or 0 to stop: ");
        scanf("%d", &c);
    }
    return 0;
}