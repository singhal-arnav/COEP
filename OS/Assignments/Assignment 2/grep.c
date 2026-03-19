#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_WORD_LEN 50
#define MAX_LINE_LEN 200

// Function to check if second string is a substring of first string
int issubstr(char *line, char *word) {
    int i = 0, j = 0, k;

    while(line[i] != '\0') {
        k = i;
        j = 0;
        while(line[k] != '\0' && word[j] != '\0' && line[k] == word[j]) {
            k++;
            j++;
        }
        if(word[j] == '\0')
            return 1;
        i++;
    }
    return 0;
}

// Function to print a string using write() system call
void myprint(char *line) {
    int i = 0;
    while(line[i] != '\0') {
        write(1, line + i, 1);
        i++;
    }
    return;
}

int main(int argc, char **argv) {
	int fd = open(argv[1], O_RDONLY), i = 0; // Open the file
	
    char word[MAX_WORD_LEN], ch;
	
	myprint("Enter the word to be searched: \n");
	while(read(0, word + i, 1) && word[i] != '\n') {
        i++;
    }
    word[i] = '\0';
    
    char line[MAX_LINE_LEN];
    
    myprint("Lines containing the word:\n");    

    i = 0;

    // Reading the file one character at a time
    while(read(fd, line + i, 1)) {
        if(line[i] == '\n') {
            line[i] = '\n';
            line[i + 1] = '\0';
            if(issubstr(line, word))
                myprint(line);
            i = 0;        
        }
        else
            i++;
    }

    // Processes the last line if it does not end with a newline character
    if (i > 0) {
        line[i] = '\n';
        line[i + 1] = '\0';
        if(issubstr(line, word))
            myprint(line);
    }
	
	return 0;
}
