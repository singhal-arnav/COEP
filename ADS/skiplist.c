#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_LEVEL 6
#define PROBABILITY 0.5

typedef struct Node {
    int key;
    struct Node *right;
    struct Node *down;
} Node;

typedef struct SkipList {
    Node *head;
    int level;  // Current maximum level
} SkipList;

SkipList* create_skiplist();
Node* create_node(int key, int level);
int random_level();
void insert(SkipList *sl, int key);
Node* search(SkipList *sl, int key);
void delete(SkipList *sl, int key);
void display(SkipList *sl);
void display_all_levels(SkipList *sl);

int main() {
    srand(time(NULL));
    
    SkipList *sl = create_skiplist();
    
    printf("Inserting elements: 3, 6, 7, 9, 12, 19, 17, 26, 21, 25\n\n");
    insert(sl, 3);
    insert(sl, 6);
    insert(sl, 7);
    insert(sl, 9);
    insert(sl, 12);
    insert(sl, 19);
    insert(sl, 17);
    insert(sl, 26);
    insert(sl, 21);
    insert(sl, 25);
    
    printf("Displaying the Skip List:\n");
    display_all_levels(sl);
    
    int search_keys[] = {7, 19, 15, 26, 30};
    for (int i = 0; i < 5; i++) {
        Node *result = search(sl, search_keys[i]);
        if (result != NULL)
            printf("Key %d: FOUND\n", search_keys[i]);
        else
            printf("Key %d: NOT FOUND\n", search_keys[i]);
    }
     
    printf("\nDeleting key 7...\n");
    delete(sl, 7);
    printf("Skip List after deleting 7:\n");
    display_all_levels(sl);
    
    printf("\nDeleting key 19...\n");
    delete(sl, 19);
    printf("Skip List after deleting 19:\n");
    display_all_levels(sl);
    
    printf("\nDeleting key 30 (not in list)...\n");
    delete(sl, 30);
    
    printf("\nFinal Skip List:\n");
    display_all_levels(sl);
    
    return 0;
}

SkipList* create_skiplist() {
    SkipList *sl = (SkipList*)malloc(sizeof(SkipList));
    sl->level = 0;
    
    Node *current = NULL;
    for (int i = 0; i <= MAX_LEVEL; i++) {
        Node *header = (Node*)malloc(sizeof(Node));
        header->key = INT_MIN;
        header->right = NULL;
        header->down = current;
        current = header;
    }
    sl->head = current;
    
    return sl;
}

Node* create_node(int key, int level) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->right = NULL;
    node->down = NULL;
    return node;
}

int random_level() {
    int level = 0;
    while (((double)rand() / RAND_MAX) < PROBABILITY && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

// a. Insert operation
void insert(SkipList *sl, int key) {
    Node *update[MAX_LEVEL + 1];
    Node *current = sl->head;
    
    for (int i = MAX_LEVEL; i >= 0; i--) {
        while (current->right != NULL && current->right->key < key) {
            current = current->right;
        }
        update[i] = current;
        
        if (current->down != NULL)
            current = current->down;
    }
    
    current = current->right;
    if (current != NULL && current->key == key) {
        printf("Key %d already exists, not inserting duplicate\n", key);
        return;
    }
    
    // Determine level for new node
    int new_level = random_level();
    
    if (new_level > sl->level) {
        sl->level = new_level;
    }
    
    Node *down_node = NULL;
    for (int i = 0; i <= new_level; i++) {
        Node *new_node = create_node(key, i);
        new_node->down = down_node;
        
        new_node->right = update[i]->right;
        update[i]->right = new_node;
        
        down_node = new_node;
    }
}

Node* search(SkipList *sl, int key) {
    Node *current = sl->head;
    
    while (current != NULL) {
        while (current->right != NULL && current->right->key < key) {
            current = current->right;
        }
        
        if (current->right != NULL && current->right->key == key) {
            return current->right;
        }
        
        current = current->down;
    }
    
    return NULL;
}

void delete(SkipList *sl, int key) {
    Node *update[MAX_LEVEL + 1];
    Node *current = sl->head;
    
    for (int i = MAX_LEVEL; i >= 0; i--) {
        while (current->right != NULL && current->right->key < key) {
            current = current->right;
        }
        update[i] = current;
        
        if (current->down != NULL)
            current = current->down;
    }
    
    current = current->right;
    if (current == NULL || current->key != key) {
        printf("Key %d not found, cannot delete\n", key);
        return;
    }
    
    for (int i = 0; i <= MAX_LEVEL; i++) {
        if (update[i]->right != NULL && update[i]->right->key == key) {
            Node *to_delete = update[i]->right;
            update[i]->right = to_delete->right;
            free(to_delete);
        }
    }
    
    while (sl->level > 0 && sl->head->right == NULL) {
        sl->level--;
        Node *temp = sl->head;
        sl->head = sl->head->down;
        free(temp);
    }
    
    printf("Key %d deleted successfully\n", key);
}

void display_level(Node *head, int level) {
    printf("Level %d: HEAD", level);
    Node *current = head->right;
    while (current != NULL) {
        printf(" -> %d", current->key);
        current = current->right;
    }
    printf(" -> NULL\n");
}

void display_all_levels(SkipList *sl) {
    Node *current = sl->head;
    int total_levels = 0;
    while (current != NULL) {
        total_levels++;
        current = current->down;
    }
    
    current = sl->head;
    int level = total_levels - 1;
    
    while (current != NULL && current->right == NULL && current->down != NULL) {
        current = current->down;
        level--;
    }
    
    while (current != NULL) {
        display_level(current, level);
        current = current->down;
        level--;
    }
    printf("\n");
}

void display(SkipList *sl) {
    Node *current = sl->head;
    
    while (current->down != NULL) {
        current = current->down;
    }
    
    printf("Skip List (Level 0): ");
    current = current->right;
    while (current != NULL) {
        printf("%d -> ", current->key);
        current = current->right;
    }
    printf("NULL\n");
}
