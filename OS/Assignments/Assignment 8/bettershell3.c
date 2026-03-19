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
#define MAX_JOBS 100

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

typedef struct job {
	int job_id;
	pid_t pid;
	pid_t pgid;
	char *command;
	int stopped;
} job;

history_ll session_history;
job jobs[MAX_JOBS];
int num_jobs = 0;
pid_t shell_pgid;
int shell_terminal;
int foreground_pgid = -1;

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
	
	session_history.num++;
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
	int file_lines = 0, flag = 0, start_line = 1;
	char line[MAX_INPUT_LEN];
	
	lseek(histfile, 0, SEEK_SET);
	
	while(read(histfile, &ch, 1)) {
		flag = 1;
		if(ch == '\n')
			file_lines++;
	}
	if(flag && ch != '\n')
		file_lines++;
	
	int total_lines = file_lines + session_history.num;
	
	if(total_lines > MAX_HIST_DISPLAY) {
		start_line = total_lines - MAX_HIST_DISPLAY + 1;
	}
	
	lseek(histfile, 0, SEEK_SET);
	
	int current_line = 1;
	int pos = 0;
	while(read(histfile, &ch, 1)) {
		if(ch == '\n') {
			line[pos] = '\0';
			if(current_line >= start_line) {
				printf("%5d  %s\n", current_line, line);
			}
			current_line++;
			pos = 0;
		}
		else {
			line[pos++] = ch;
		}
	}
	if(pos > 0) {
		line[pos] = '\0';
		if(current_line >= start_line) {
			printf("%5d  %s\n", current_line, line);
		}
		current_line++;
	}
	
	history_node *p = session_history.head;
	while(p) {
		if(current_line >= start_line) {
			printf("%5d  %s\n", current_line, p->input);
		}
		current_line++;
		p = p->next;
	}
	
	return;
}

void update_jobs() {
	int i = 0;
	while(i < num_jobs) {
		int status;
		pid_t result = waitpid(jobs[i].pid, &status, WNOHANG | WUNTRACED | WCONTINUED);
		
		if(result > 0) {
			if(WIFEXITED(status) || WIFSIGNALED(status)) {
				free(jobs[i].command);
				for(int j = i; j < num_jobs - 1; j++) {
					jobs[j] = jobs[j + 1];
				}
				num_jobs--;
				continue;
			}
			else if(WIFSTOPPED(status)) {
				jobs[i].stopped = 1;
			}
			else if(WIFCONTINUED(status)) {
				jobs[i].stopped = 0;
			}
		}
		i++;
	}
	
	for(int i = 0; i < num_jobs; i++) {
		jobs[i].job_id = i + 1;
	}
}

void add_job(pid_t pid, pid_t pgid, char *command, int stopped) {
	if(num_jobs < MAX_JOBS) {
		jobs[num_jobs].job_id = num_jobs + 1;
		jobs[num_jobs].pid = pid;
		jobs[num_jobs].pgid = pgid;
		jobs[num_jobs].command = (char*)malloc(strlen(command) + 1);
		strcpy(jobs[num_jobs].command, command);
		jobs[num_jobs].stopped = stopped;
		num_jobs++;
	}
}

void display_jobs() {
	update_jobs();
	
	for(int i = 0; i < num_jobs; i++) {
		printf("[%d]  %c %s\t\t%s\n", 
			jobs[i].job_id,
			jobs[i].stopped ? 'T' : 'R',
			jobs[i].stopped ? "Stopped" : "Running",
			jobs[i].command);
	}
}

void fg_job(int job_id) {
	update_jobs();
	
	int job_index = -1;
	if(job_id == 0) {
		if(num_jobs > 0)
			job_index = num_jobs - 1;
	}
	else {
		for(int i = 0; i < num_jobs; i++) {
			if(jobs[i].job_id == job_id) {
				job_index = i;
				break;
			}
		}
	}
	
	if(job_index == -1) {
		printf("bettershell: fg: no such job\n");
		return;
	}
	
	pid_t pgid = jobs[job_index].pgid;
	char *command = (char*)malloc(strlen(jobs[job_index].command) + 1);
    strcpy(command, jobs[job_index].command);
	int was_stopped = jobs[job_index].stopped;
	
	free(jobs[job_index].command);
	for(int i = job_index; i < num_jobs - 1; i++) {
		jobs[i] = jobs[i + 1];
	}
	num_jobs--;
	
	for(int i = 0; i < num_jobs; i++) {
		jobs[i].job_id = i + 1;
	}
	
	tcsetpgrp(shell_terminal, pgid);
	foreground_pgid = pgid;
	
	if(was_stopped) {
		kill(-pgid, SIGCONT);
	}
	
	int status;
	waitpid(-pgid, &status, WUNTRACED);
	
	tcsetpgrp(shell_terminal, shell_pgid);
	foreground_pgid = -1;
	
	if(WIFSTOPPED(status)) {
		add_job(pgid, pgid, command, 1);
		printf("\n[%d]  T Stopped\t\t%s\n", num_jobs, command);
	}
	
	free(command);
}

void bg_job(int job_id) {
	update_jobs();
	
	int job_index = -1;
	if(job_id == 0) {
		if(num_jobs > 0)
			job_index = num_jobs - 1;
	}
	else {
		for(int i = 0; i < num_jobs; i++) {
			if(jobs[i].job_id == job_id) {
				job_index = i;
				break;
			}
		}
	}
	
	if(job_index == -1) {
		printf("bettershell: bg: no such job\n");
		return;
	}
	
	if(!jobs[job_index].stopped) {
		printf("bettershell: bg: job already in background\n");
		return;
	}
	
	jobs[job_index].stopped = 0;
	kill(-jobs[job_index].pgid, SIGCONT);
	printf("[%d]  R Running\t\t%s\n", jobs[job_index].job_id, jobs[job_index].command);
}

void sigint_handler(int sig) {
	if(foreground_pgid > 0) {
		kill(-foreground_pgid, SIGINT);
	}
	else {
		printf("\n");
		if(in_readline) {
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	return;
}

void sigtstp_handler(int sig) {
	if(foreground_pgid > 0) {
		kill(-foreground_pgid, SIGTSTP);
	}
	else {
		printf("\n");
		if(in_readline) {
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
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
    
    shell_terminal = STDIN_FILENO;
    shell_pgid = getpid();
    
    if(setpgid(shell_pgid, shell_pgid) < 0) {
    	perror("Couldn't put the shell in its own process group");
    	exit(1);
    }
    
    tcsetpgrp(shell_terminal, shell_pgid);
    
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);

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

    while(1) {
    	update_jobs();
    	
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
		else if(!strcmp(args[0], "jobs"))
			flag = 5;
		else if(!strcmp(args[0], "fg"))
			flag = 6;
		else if(!strcmp(args[0], "bg"))
			flag = 7;
		else if(!strcmp(args[0], "exit")) {
			update_shell_history();
			exit(0);
		}
		else
			flag = 8;
		
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
        	else {
            	args[i++] = token;
            }        
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
        	display_jobs();
        }
        else if(flag == 6) {
        	int job_id = 0;
        	if(args[1])
        		job_id = atoi(args[1]);
        	fg_job(job_id);
        }
        else if(flag == 7) {
        	int job_id = 0;
        	if(args[1])
        		job_id = atoi(args[1]);
        	bg_job(job_id);
        }
        else if(flag == 8) {
			char *pipe_segments[MAX_PIPES];
			int num_segments = 0;
			
			split_by_pipes(input_copy, pipe_segments, &num_segments);
			
			if(num_segments == 1) {
				int pid = fork();
				if(pid == 0) {
					pid_t child_pid = getpid();
					setpgid(child_pid, child_pid);
					
					signal(SIGINT, SIG_DFL);
					signal(SIGTSTP, SIG_DFL);
					signal(SIGTTOU, SIG_DFL);
					signal(SIGTTIN, SIG_DFL);
					
					tcsetpgrp(shell_terminal, child_pid);
					
					execute_command(args);
				}
				
				setpgid(pid, pid);
				
				tcsetpgrp(shell_terminal, pid);
				foreground_pgid = pid;
				
				int status;
				waitpid(pid, &status, WUNTRACED);
				
				tcsetpgrp(shell_terminal, shell_pgid);
				foreground_pgid = -1;
				
				if(WIFSTOPPED(status)) {
					add_job(pid, pid, input_copy, 1);
					printf("\n[%d]  T Stopped\t\t%s\n", num_jobs, input_copy);
				}
			}
			else {
				int pipes[MAX_PIPES][2];
				int num_pipes = num_segments - 1;
				
				for(int p = 0; p < num_pipes; p++) {
					pipe(pipes[p]);
				}
				
				pid_t pgid = 0;
				
				for(int c = 0; c < num_segments; c++) {
					char *cmd_args[MAX_ARG_NUM];
					parse_command(pipe_segments[c], cmd_args);
					
					int pid = fork();
					if(pid == 0) {
						if(c == 0) {
							pid_t child_pid = getpid();
							setpgid(child_pid, child_pid);
							pgid = child_pid;
						}
						else {
							setpgid(0, pgid);
						}
						
						signal(SIGINT, SIG_DFL);
						signal(SIGTSTP, SIG_DFL);
						signal(SIGTTOU, SIG_DFL);
						signal(SIGTTIN, SIG_DFL);
						
						if(c == 0) {
							tcsetpgrp(shell_terminal, getpid());
						}
						
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
					
					if(c == 0) {
						pgid = pid;
						setpgid(pid, pid);
					}
					else {
						setpgid(pid, pgid);
					}
				}
				
				for(int p = 0; p < num_pipes; p++) {
					close(pipes[p][0]);
					close(pipes[p][1]);
				}
				
				tcsetpgrp(shell_terminal, pgid);
				foreground_pgid = pgid;
				
				int status;
				for(int c = 0; c < num_segments; c++) {
					waitpid(-pgid, &status, WUNTRACED);
				}
				
				tcsetpgrp(shell_terminal, shell_pgid);
				foreground_pgid = -1;
				
				if(WIFSTOPPED(status)) {
					add_job(pgid, pgid, input_copy, 1);
					printf("\n[%d]  T Stopped\t\t%s\n", num_jobs, input_copy);
				}
			}
		}
    }
	
	return 0;
}
