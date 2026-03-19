#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_WORD_LENGTH 50

typedef struct trie_node {
    struct trie_node* children[ALPHABET_SIZE];
    int is_end_node;
} trie_node;

typedef struct trie {
	trie_node *root;
} trie;

void init_trie(trie *tp);
trie_node* create_node();
void insert(trie *tp, char* word);
int search(trie *tp, char* word);
void find_all_words(trie_node* node, char* prefix, int length);
void auto_suggest(trie *tp, char* prefix);
void free_trie(trie_node* node);

int main() {
    char* dictionary[] = {
        "apple", "application", "apply", "approve", "april",
        "ball", "balloon", "banana", "band", "bank",
        "cat", "cake", "call", "camera", "camp",
        "car", "card", "care", "careful", "carry",
        "dog", "door", "down", "draw", "dream",
        "dress", "drink", "drive", "drop", "during",
        "elephant", "eleven", "email", "empty", "end",
        "energy", "engine", "enjoy", "enough", "enter",
        "family", "famous", "far", "farm", "fast",
        "father", "fear", "feel", "field", "fight",
        "game", "garden", "gate", "general", "gift",
        "happy", "hard", "hat", "have", "head",
        "ice", "idea", "image", "important", "improve",
        "include", "increase", "indeed", "industry", "information",
        "jump", "june", "jungle", "junior", "just",
        "justice", "justify", "key", "kind", "king",
        "kitchen", "knee", "knife", "know", "knowledge",
        "land", "language", "large", "last", "late",
        "laugh", "launch", "law", "lead", "learn",
        "machine", "magic", "main", "major", "make",
        "nature", "near", "necessary", "need", "network",
        "ocean", "offer", "office", "often", "oil",
        "old", "once", "only", "open", "option",
        "paper", "parent", "park", "part", "party",
        "pass", "past", "path", "pattern", "pay",
        "quality", "question", "quick", "quiet", "quite",
        "race", "rain", "raise", "range", "rate",
        "reach", "read", "ready", "real", "reason",
        "science", "screen", "sea", "season", "seat",
        "tax", "tea", "teach", "team", "technology"
    };
    
    int dict_size = sizeof(dictionary) / sizeof(dictionary[0]);
    
    trie t;
    init_trie(&t);
    
    printf("Inserting %d words into the Trie.\n\n", dict_size);
    
    for(int i = 0; i < dict_size; i++)
        insert(&t, dictionary[i]);
    
    char word[MAX_WORD_LENGTH];
    printf("Enter word to be searched: ");
    scanf("%s", word);
    
    if(search(&t, word))
        printf("'%s' found in dictionary\n", word);
    else
        printf("'%s' not found in dictionary\n", word);  
    
    printf("\nEnter a prefix to get suggestions: ");
    scanf("%s", word);
    
    if(search(&t, word))
        printf("'%s' is a complete word in the dictionary!\n", word);
    
    auto_suggest(&t, word);
    
    free_trie(t.root);
    
    return 0;
}

void init_trie(trie *tp) {
	tp->root = create_node();
	return;
}

trie_node* create_node() {
    trie_node* node = (trie_node*)malloc(sizeof(trie_node));
    node->is_end_node = 0;
    for(int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

void insert(trie *tp, char *word) {
    trie_node *current = tp->root;
    int length = strlen(word);
    
    for(int i = 0; i < length; i++) {
        int index = word[i] - 'a';
        if(index < 0 || index >= ALPHABET_SIZE) {
        	printf("Error: '%s' cannot be inserted into the trie.\n", word);
        	exit(1);
        }
        
        if(current->children[index] == NULL) {
            current->children[index] = create_node();
        }
        current = current->children[index];
    }
    current->is_end_node = 1;
}

int search(trie* tp, char* word) {
    trie_node* current = tp->root;
    int length = strlen(word);
    
    for(int i = 0; i < length; i++) {
        int index = word[i] - 'a';
        if(index < 0 || index >= ALPHABET_SIZE)
        	return 0;
        if(current->children[index] == NULL)
            return 0;
        current = current->children[index];
    }
    return (current != NULL && current->is_end_node);
}

void find_all_words(trie_node* node, char* prefix, int length) {
    if(node->is_end_node) {
        prefix[length] = '\0';
        printf("%s\n", prefix);
    }
    
    for(int i = 0; i < ALPHABET_SIZE; i++) {
        if(node->children[i] != NULL) {
            prefix[length] = 'a' + i;
            find_all_words(node->children[i], prefix, length + 1);
        }
    }
}

void auto_suggest(trie *tp, char* prefix) {
    trie_node* current = tp->root;
    int length = strlen(prefix);
    
    for(int i = 0; i < length; i++) {
        int index = prefix[i] - 'a';
        if(index < 0 || index >= ALPHABET_SIZE || current->children[index] == NULL) {
            printf("No suggestions found for '%s'\n", prefix);
            return;
        }
        current = current->children[index];
    }
    
    printf("Auto-suggestions for '%s':\n", prefix);
    char word[MAX_WORD_LENGTH];
    strcpy(word, prefix);
    find_all_words(current, word, length);
}

void free_trie(trie_node* node) {
    if(node == NULL) return;
    
    for(int i = 0; i < ALPHABET_SIZE; i++) {
        if(node->children[i] != NULL) {
            free_trie(node->children[i]);
        }
    }
    free(node);
}
