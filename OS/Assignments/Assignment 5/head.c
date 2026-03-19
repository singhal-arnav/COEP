#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define DEFAULT_N 10

void head(int fd, int n) {
    char buf[1];
    int lines = 0;

    while(read(fd, buf, 1) == 1) {
        write(1, buf, 1);
        if(buf[0] == '\n') {
            lines++;
            if(lines == n)
                break;
        }
    }
}

int main(int argc, char *argv[]) {
    int n = DEFAULT_N, fd, file_count = 0;

    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-n") == 0) {
            if(i + 1 >= argc) {
                printf(2, "head: option requires an argument -- n\n");
                exit();
            }
            n = atoi(argv[i + 1]);
            i++; // skip number
        } 
        else
            file_count++;
    }

    if(argc == 1 || file_count == 0) {
        head(0, n);
        exit();
    }

    int printed = 0;
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-n") == 0) {
            i++;
            continue; 
        }

        fd = open(argv[i], O_RDONLY);
        if(fd < 0) {
            printf(2, "head: failed to open %s\n", argv[i]);
            exit();
        }

        if(file_count > 1) {
            if(printed > 0) 
                printf(1, "\n");
            printf(1, "==> %s <==\n", argv[i]);
        }

        head(fd, n);
        close(fd);
        printed++;
    }

    exit();
}
