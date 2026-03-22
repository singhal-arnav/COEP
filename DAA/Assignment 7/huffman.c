#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char ch;
    int freq;
    struct Node *left;
    struct Node *right;
};

struct Node* heap[200];
int heapSize = 0;

struct Node* createNode(char ch, int freq) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->ch = ch;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void swap(int i, int j) {
    struct Node* temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void heapifyUp(int index) {
    while(index > 0) {
        int parent = (index - 1) / 2;
        if(heap[parent]->freq > heap[index]->freq) {
            swap(parent, index);
            index = parent;
        }
        else
            break;
    }
}

void heapifyDown(int index) {
    while(1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if(left < heapSize && heap[left]->freq < heap[smallest]->freq)
            smallest = left;

        if(right < heapSize && heap[right]->freq < heap[smallest]->freq)
            smallest = right;

        if(smallest != index) {
            swap(index, smallest);
            index = smallest;
        } 
        else
            break;
    }
}

void insertHeap(struct Node* node) {
    heap[heapSize] = node;
    heapifyUp(heapSize);
    heapSize++;
}

struct Node* extractMin() {
    struct Node* min = heap[0];
    heap[0] = heap[heapSize - 1];
    heapSize--;
    heapifyDown(0);
    return min;
}

void printCodes(struct Node* root, int code[], int top, char chars[], char codes[][100], int *index) {
    if(root->left) {
        code[top] = 0;
        printCodes(root->left, code, top + 1, chars, codes, index);
    }

    if(root->right) {
        code[top] = 1;
        printCodes(root->right, code, top + 1, chars, codes, index);
    }

    if(!root->left && !root->right) {
        printf("%c: ", root->ch);
        chars[*index] = root->ch;

        for(int i = 0; i < top; i++) {
            printf("%d", code[i]);
            codes[*index][i] = code[i] + '0';
        }

        codes[*index][top] = '\0';
        printf("\n");
        (*index)++;
    }
}

int main() {
    int n;

    printf("Enter number of characters: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        char ch;
        int freq;

        printf("Enter character: ");
        scanf(" %c", &ch);
        printf("Enter frequency: ");
        scanf("%d", &freq);

        insertHeap(createNode(ch, freq));
    }

    while(heapSize > 1) {
        struct Node* left = extractMin();
        struct Node* right = extractMin();

        struct Node* newNode = createNode('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        insertHeap(newNode);
    }

    struct Node* root = extractMin();

    int code[100];
    char chars[100];
    char codes[100][100];
    int index = 0;

    printf("Huffman Codes:\n");
    printCodes(root, code, 0, chars, codes, &index);

    char input[1000];
    printf("Enter string to encode: ");
    scanf("%s", input);

    int totalBits = 0;

    printf("Encoded string:\n");

    for(int i = 0; input[i] != '\0'; i++) {
        for(int j = 0; j < index; j++) {
            if(input[i] == chars[j]) {
                printf("%s", codes[j]);
                totalBits += strlen(codes[j]);
                break;
            }
        }
    }

    printf("\nTotal number of bits required: %d\n", totalBits);

    return 0;
}

