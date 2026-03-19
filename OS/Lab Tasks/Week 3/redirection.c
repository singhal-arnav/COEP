#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    close(1);
    open("text.txt", O_WRONLY | O_CREAT, 0644);
    printf("This line will be written inside a file instead of being displayed in the terminal\n");
    
    return 0;
}
