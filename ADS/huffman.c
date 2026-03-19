#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

struct MinHeapNode* newNode(char data, unsigned freq);
struct MinHeap* createMinHeap(unsigned capacity);
void swapNode(struct MinHeapNode** a, struct MinHeapNode** b);
void minHeapify(struct MinHeap* minHeap, int idx);
int isSizeOne(struct MinHeap* minHeap);
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode);
void buildMinHeap(struct MinHeap* minHeap);
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size);
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size);
void printCodes(struct MinHeapNode* root, int arr[], int top);
void storeCodes(struct MinHeapNode* root, int arr[], int top, char codes[256][100]);
void encodeText(char text[], char codes[256][100], char encoded[]);
void decodeText(struct MinHeapNode* root, char encoded[]);
void countFreq(char text[], char *characters, int freq[], int *size);

int main() {
    char text[500];
    printf("Enter the text to be encoded: ");
    fgets(text, 500, stdin);
    text[strcspn(text, "\n")] = '\0';

    char characters[256];
    int freq[256];
    int size = 0;

    countFreq(text, characters, freq, &size);

    struct MinHeapNode* root = buildHuffmanTree(characters, freq, size);

    int arr[MAX_TREE_HT], top = 0;
    printf("\nHuffman Codes:\n");
    printCodes(root, arr, top);

    char codes[256][100];
    storeCodes(root, arr, top, codes);

    char encoded[1000];
    encodeText(text, codes, encoded);

    printf("\nEncoded Message: %s\n", encoded);
    decodeText(root, encoded);
    
    return 0;
}

struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left= 2*idx + 1;
    int right= 2*idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i= (i - 1)/2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i= (n - 1)/2; i >= 0; i--)
        minHeapify(minHeap, i);
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void printCodes(struct MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!(root->left) && !(root->right)) {
        printf("character: %c | freq: %d | code: ", root->data, root->freq);
        for (int i = 0; i < top; i++)
            printf("%d", arr[i]);
        printf("\n");
    }
}

void storeCodes(struct MinHeapNode* root, int arr[], int top, char codes[256][100]) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1, codes);
    }
    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, codes);
    }
    if (!(root->left) && !(root->right)) {
        char temp[100] = "";
        for (int i = 0; i < top; i++) {
            char bit = arr[i] + '0';
            strncat(temp, &bit, 1);
        }
        strcpy(codes[(unsigned char)root->data], temp);
    }
}

void encodeText(char text[], char codes[256][100], char encoded[]) {
    strcpy(encoded, "");
    for (int i = 0; text[i] != '\0'; i++) {
        strcat(encoded, codes[(unsigned char)text[i]]);
    }
}

void decodeText(struct MinHeapNode* root, char encoded[]) {
    printf("decoded Text: ");
    struct MinHeapNode* current = root;
    for (int i = 0; encoded[i] != '\0'; i++) {
        if (encoded[i] == '0')
            current = current->left;
        else
            current = current->right;

        if (!(current->left) && !(current->right)) {
            printf("%c", current->data);
            current = root;
        }
    }
    printf("\n");
}

void countFreq(char text[], char *characters, int freq[], int *size) {
    int i;
    int visited[256] = {0};
    *size = 0;
    for (i = 0; text[i] != '\0'; i++) {
        unsigned char ch = text[i];
        if (!visited[ch]) {
            visited[ch] = 1;
            characters[*size] = ch;
            freq[*size] = 1;
            (*size)++;
        } else {
            for (int j = 0; j < *size; j++) {
                if (characters[j] == ch) {
                    freq[j]++;
                    break;
                }
            }
        }
    }
}
