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
#include <signal.h>

#define MAX_DIR_LEN 100
#define MAX_PROMPT_LEN 100
#define MAX_COMM_LEN 200
#define MAX_ARG_NUM 10
#define MAX_FILES_LEN 300
#define MAX_PATH_LEN 400
#define MAX_HOME_LEN 100
#define MAX_HIST_DISPLAY 1000
#define MAX_PIPES 10
#define MAX_INPUT_LEN 1024

char path[MAX_PATH_LEN];
char PS1[MAX_PROMPT_LEN] = "\\w$ ";
int in_readline;
char home[MAX_HOME_LEN] = "/home/";
int histfile;

typedef struct history_node {
	char *input;
	struct history_node *next;
} history_node;

typedef struct history_ll {
	history_node *head;
	int num;
} history_ll;

history_ll session_history;

void init_session_history() {
	session_history.head = NULL;
	session_history.num = 0;
	return;
}

void add_session_history(char *input) {
	history_node *n = (history_node*)malloc(sizeof(history_node));
	n->input = (char*)malloc(strlen(input) + 1);
	n->next = NULL;
	strcpy(n->input, input);
	
	if(session_history.head) {
		history_node *p = session_history.head;
		while(p->next)
			p = p->next;		
		if(!strcmp(input, p->input)) {
			free(n);
			return;
		}
		else
			p->next = n;
	}
	else
		session_history.head = n;
	
	return;
}

void update_shell_history() {
	lseek(histfile, 0, SEEK_END);
	
	while(session_history.head) {
		write(histfile, session_history.head->input, strlen(session_history.head->input));
		write(histfile, "\n", 1);
		history_node *p = session_history.head;
		session_history.head = p->next;
		free(p);
	}
	return;
}

void display_history() {
	char ch;
	int n = 0, flag = 0, ndiff;
	
	lseek(histfile, 0, SEEK_SET);
	
	while(read(histfile, &ch, 1)) {
		flag = 1;
		if(ch == '\n')
			n++;
	}
	if(flag && ch != '\n')
		n++;
	
	printf("%d\n", n);
	
	if(MAX_HIST_DISPLAY <= session_history.num) {
		int i = 0;
		history_node *p = session_history.head;
		
		
	}
	else {
	}
	
	return;
}

void sigint_handler(int sig) {
	printf("\n");
	if(in_readline) {
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return;
}

void sigtstp_handler(int sig) {
  printf("\n");
	if(in_readline) {
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return;
}

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
	char cwd[MAX_DIR_LEN], *cwd_tilde;
    getcwd(cwd, sizeof(cwd));
    
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

void split_by_pipes(char *input, char *pipe_segments[MAX_PIPES], int *num_segments) {
	*num_segments = 0;
	char *start = input;
	char *current = input;
	
	while(*current) {
		if(*current == '|') {
			*current = '\0';
			pipe_segments[(*num_segments)++] = start;
			start = current + 1;
		}
		current++;
	}
	pipe_segments[(*num_segments)++] = start;
}

void parse_command(char *cmd_str, char *args[MAX_ARG_NUM]) {
	char *token;
	char buffer[256];
	int i = 0;
	
	token = strtok(cmd_str, " ");
	while(token && i < MAX_ARG_NUM - 1) {
		if(token[0] == '\'' || token[0] == '\"') {
			strcpy(buffer, token + 1);
			while(token[strlen(token) - 1] != '\"' && token[strlen(token) - 1] != '\'') {
				strcat(buffer, " ");
				token = strtok(NULL, " ");
				strcat(buffer, token);
			}
			buffer[strlen(buffer) - 1] = '\0';
			args[i++] = strdup(buffer);
		}
		else {
			args[i++] = strdup(token);
		}
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}

void execute_command(char *cmd_args[MAX_ARG_NUM]) {
	int in_fd = -1, out_fd = -1;

	for(int j = 0; cmd_args[j] != NULL; j++) {
		if(strcmp(cmd_args[j], "<") == 0 && cmd_args[j+1]) {
			in_fd = open(cmd_args[j+1], O_RDONLY);
			if(in_fd < 0) {
				printf("%s\n", strerror(errno));
				exit(1);
			}
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);

			for(int k = j; cmd_args[k-1] != NULL; k++) {
				free(cmd_args[k]);
				cmd_args[k] = cmd_args[k+2];
			}
			j--;
		}
		else if(strcmp(cmd_args[j], ">") == 0 && cmd_args[j+1]) {
			out_fd = open(cmd_args[j+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(out_fd < 0) {
				printf("%s\n", strerror(errno));
				exit(1);
			}
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);

			for(int k = j; cmd_args[k-1] != NULL; k++) {
				free(cmd_args[k]);
				cmd_args[k] = cmd_args[k+2];
			}
			j--; 
		}
	}
	
	char path_copy[MAX_PATH_LEN];
	strcpy(path_copy, path);
	
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	myexecvp(cmd_args[0], cmd_args);
	printf("bettershell: %s: %s\n", cmd_args[0], strerror(errno));
	exit(1);
}

int main() {
    strcpy(path, getenv("PATH"));
    char histfilename[200];
    
    init_session_history();

    char cwd[MAX_DIR_LEN], *prompt, *input, *args[MAX_ARG_NUM];
    
    strcat(home, getlogin());
    strcpy(histfilename, home);
    strcat(histfilename, "/");
    strcat(histfilename, ".bettershell_history");
    
    if((histfile = open(histfilename, O_RDWR | O_CREAT | O_APPEND, 0644)) == -1) {
    	printf("Failed to open history file\n");
    	exit(1);
    }
    
    prompt = set_prompt(PS1, MAX_PROMPT_LEN);
    
	  signal(SIGINT, sigint_handler);
	  signal(SIGTSTP, sigtstp_handler);

    while(1) {
		in_readline = 1;
        input = readline(prompt);
        input = replace_substr(input, "~", home);
		in_readline = 0;
        if(!input) {
        	update_shell_history();
        	exit(0);
        }
        
        add_session_history(input);
        
        int flag;
        
        char input_copy[MAX_INPUT_LEN];
        strcpy(input_copy, input);
        
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
		else if(!strcmp(args[0], "history"))
			flag = 4;
		else if(!strcmp(args[0], "exit")) {
			update_shell_history();
			exit(0);
		}
		else
			flag = 5;
		
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
        	display_history();
        }
        else if(flag == 5) {
			char *pipe_segments[MAX_PIPES];
			int num_segments = 0;
			
			split_by_pipes(input_copy, pipe_segments, &num_segments);
			
			if(num_segments == 1) {
				int pid = fork();
				if(pid == 0) {
					execute_command(args);
				}
				wait(NULL);
			}
			else {
				int pipes[MAX_PIPES][2];
				int num_pipes = num_segments - 1;
				
				for(int p = 0; p < num_pipes; p++) {
					pipe(pipes[p]);
				}
				
				for(int c = 0; c < num_segments; c++) {
					char *cmd_args[MAX_ARG_NUM];
					parse_command(pipe_segments[c], cmd_args);
					
					int pid = fork();
					if(pid == 0) {
						if(c > 0) {
							dup2(pipes[c-1][0], STDIN_FILENO);
						}
						if(c < num_pipes) {
							dup2(pipes[c][1], STDOUT_FILENO);
						}
						
						for(int p = 0; p < num_pipes; p++) {
							close(pipes[p][0]);
							close(pipes[p][1]);
						}
						
						execute_command(cmd_args);
					}
				}
				
				for(int p = 0; p < num_pipes; p++) {
					close(pipes[p][0]);
					close(pipes[p][1]);
				}
				
				for(int c = 0; c < num_segments; c++) {
					wait(NULL);
				}
			}
		}
    }
	
	return 0;
}
