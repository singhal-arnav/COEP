#include <stdio.h>
#include <unistd.h>

#define MAX_PATH_LEN 100

int main() {
    char cwd[MAX_PATH_LEN];

    getcwd(cwd, MAX_PATH_LEN);
	printf("Current working directory: %s\n", cwd);
    
	printf("Changing directory\n");

	if(!chdir("..")) {
        printf("Directory changed successfully\n");

        getcwd(cwd, MAX_PATH_LEN);
	    printf("New working directory: %s\n", cwd);
    }
    else
        printf("Directory change failed\n");

	return 0;
}
