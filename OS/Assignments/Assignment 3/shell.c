#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

#define MAX_DIR_LEN 100
#define MAX_PROMPT_LEN 100
#define MAX_COMM_LEN 200
#define MAX_ARG_NUM 10
#define MAX_FILES_LEN 300
#define MAX_PATH_LEN 400
#define MAX_HOME_LEN 100

char path[MAX_PATH_LEN];
char PS1[MAX_PROMPT_LEN] = "\\w$ ";

char *replace_substr(char *str, char *old, char *new) {
    if(!str || !old || !new)
    	return NULL;

    int len_str = strlen(str), len_old = strlen(old), len_new = strlen(new);

    if(len_old == 0)
    	return NULL;

    int count = 0;
    char *tmp = str;
    while((tmp = strstr(tmp, old))) {
        count++;
        tmp += len_old;
    }

    int new_len = len_str + (len_new - len_old) * count + 1;
    char *result = (char*)malloc(new_len);
    
    char *current = str, *out = result;
    while ((tmp = strstr(current, old))) {
        int bytes_to_copy = tmp - current;
        memcpy(out, current, bytes_to_copy);
        out += bytes_to_copy;
        memcpy(out, new, len_new);
        out += len_new;
        current = tmp + len_old;
    }
    strcpy(out, current);

    return result;
}

char *set_prompt(char *prompt, int max_len) {
	char cwd[MAX_DIR_LEN], home[MAX_HOME_LEN] = "/home/", *cwd_tilde;
    getcwd(cwd, sizeof(cwd));
    
    strcat(home, getlogin());
    cwd_tilde = replace_substr(cwd, home, "~");
	
	return replace_substr(prompt, "\\w", cwd_tilde	);
}

int myexecvp(char *file, char **argv) {
    int retval;
	
	if(file[0] != '/' && file[0] != '.') {
		char *dir, *dir_file;
		dir = strtok(path, ":");
		while(dir) {
		    char buff[1], command[200];
		    int flag = 0;
		    
		    DIR *dp = opendir(dir);
		    if (dp) {
		        struct dirent *entry;
		        while((entry = readdir(dp)) != NULL) {
		            if(strcmp(entry->d_name, file) == 0) {
		                flag = 1;
		                break;
		            }
		        }
		        closedir(dp);
		    }
		    
		    if(flag) {
		        strcpy(command, dir);
		        strcat(command, "/");
		        strcat(command, file);
		        retval = execv(command, argv);
		        return retval;
		    }

		    dir = strtok(NULL, ":");    
		}
	}
	
	int fd;
	if((fd = open(file, O_RDONLY)) != -1) {
		close(fd);
    	retval = execv(file, argv);
    }
    	
    return retval;
}

int main() {
    strcpy(path, getenv("PATH"));

    char cwd[MAX_DIR_LEN], *prompt, *input, *args[MAX_ARG_NUM];
    
    prompt = set_prompt(PS1, MAX_PROMPT_LEN);
    
    while(1) {    	
        input = readline(prompt);
        if(!input)
        	exit(0);
        
        int flag;
        
        char *command = strtok(input, " "), *token;
        char buffer[256];
        args[0] = command;
        int i = 1;
		
		if(!strcmp(args[0], "cd"))
			flag = 1;
		else if(!strncmp(args[0], "PS1=", 4))
			flag = 2;
		else if(!strncmp(args[0], "PATH=", 5))
			flag = 3;
		else if(!strcmp(args[0], "exit"))
			exit(0);
		else
			flag = 4;
		
        while((token = strtok(NULL, " "))) {
        	if(token[0] == '\'' || token[0] == '\"') {
        		strcpy(buffer, token + 1);
        		while(token[strlen(token) - 1] != '\"' && token[strlen(token) - 1] != '\'') {
		    		strcat(buffer, " ");
		    		token = strtok(NULL, " ");
		    		strcat(buffer, token);
		    	}
		    	buffer[strlen(buffer) - 1] = '\0';
		    	args[i++] = buffer;
        	}
        	else
            	args[i++] = token;        
        }
        
        args[i] = NULL;
        
        if(flag == 1) {
        	if(args[1])
        		chdir(args[1]);
        	else
				chdir("/home/arnav");
        	prompt = set_prompt(PS1, MAX_PROMPT_LEN);
        }
        else if(flag == 2) {
        	int j = 0;
        	if(args[0][4] == '\'' || args[0][4] == '\"') {
        		strcpy(PS1, args[0] + 5);
        		while(args[j] && args[j][strlen(args[j]) - 1] != '\'' && args[j][strlen(args[j]) - 1] != '\"') {
        			strcat(PS1, " ");
        			strcat(PS1, args[++j]);
        			printf("%s\n", args[j]);
        		}
        		PS1[strlen(PS1) - 1] = '\0';
        		free(prompt);
        		prompt = set_prompt(PS1, MAX_PROMPT_LEN);
        	}
        	else {
        		strcpy(PS1, args[0] + 4);
        		free(prompt);
        		prompt = set_prompt(PS1, MAX_PROMPT_LEN);
        	}
        }
        else if(flag == 3) {
        	int j = 0;
        	if(args[0][5] == '\'' || args[0][5] == '\"') {
        		strcpy(path, args[0] + 6);
        		while(args[j] && args[j][strlen(args[j]) - 1] != '\'' && args[j][strlen(args[j]) - 1] != '\"') {
        			strcat(path, " ");
        			strcat(path, args[++j]);
        		}
        		path[strlen(path) - 1] = '\0';
        	}
        	else
        		strcpy(path, args[0] + 5);
        }
        else if(flag == 4) {
		   	int pid = fork();
			if(pid == 0) {
				int in_fd = -1, out_fd = -1;

				for(int j = 0; args[j] != NULL; j++) {
				    if(strcmp(args[j], "<") == 0 && args[j+1]) {
				        in_fd = open(args[j+1], O_RDONLY);
				        if(in_fd < 0) {
				            printf("%s\n", strerror(errno));
				            exit(1);
				        }
				        dup2(in_fd, STDIN_FILENO);
				        close(in_fd);

				        for(int k = j; args[k-1] != NULL; k++) {
				            args[k] = args[k+2];
				        }
				        j--;
				    }
				    else if(strcmp(args[j], ">") == 0 && args[j+1]) {
				        out_fd = open(args[j+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				        if(out_fd < 0) {
				            printf("%s\n", strerror(errno));
				            exit(1);
				        }
				        dup2(out_fd, STDOUT_FILENO);
				        close(out_fd);

				        for(int k = j; args[k-1] != NULL; k++) {
				            args[k] = args[k+2];
				        }
				        j--; 
				    }
				}
				
				myexecvp(command, args);
				printf("%s\n", strerror(errno));
				exit(1);
			}
			wait(NULL);
		}
    }
	
	return 0;
}
