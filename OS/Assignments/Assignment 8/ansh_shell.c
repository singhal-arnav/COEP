#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>

#define MAX_HISTORY 64
#define CMD_BUF_SIZE 1024
#define MAX_ARGS 50
#define MAX_PIPE_CMDS 8

char prompt_str[PATH_MAX + 2];
int prompt_mode = 1;
char * history_list[MAX_HISTORY];
int history_count = 0;

 
void print_error_message(const char *format, const char *arg) {
    for (int i = 0; format[i] != '\0'; ++i) {
        if (format[i] == '%' && format[i + 1] == 's') {
            i++; // skip '%'
            for (int j = 0; arg[j] != '\0'; ++j) {
                write(2, &arg[j], 1);}
        } else{
            write(2, &format[i], 1);
        }
    }
}

void update_prompt() {
    if (prompt_mode) {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            snprintf(prompt_str, sizeof(prompt_str), "%s$ ", cwd);
        } else  { 
            strcpy(prompt_str, "$ ");
        }
    }
}

//function set global prompt mode
void change_str_prompt(char *new_prompt) {
    // Trims double quotes in string
    if (*new_prompt == '"') {
        new_prompt++;
        new_prompt[strlen(new_prompt) - 1] = '\0';
    }
    if (strcmp(new_prompt, "\\w$") == 0) {
        prompt_mode = 1; // CWD prompt
        return;
    }

    prompt_mode = 0; // Custom prompt
    snprintf(prompt_str, sizeof(prompt_str), "%s ", new_prompt);
}

//history functionality

void add_to_history(const char * line)  {
    if (history_count > 0 && strcmp(history_list[history_count - 1], line) == 0)    {
        return;
    }
    if (history_count < MAX_HISTORY)    {
        history_list[history_count++] = strdup(line);
    }  else    {
        free(history_list[0]);
        for (int i = 1; i < MAX_HISTORY; i++)   {
            history_list[i -1] = history_list[i];
        }
        history_list[MAX_HISTORY - 1] = strdup(line);
    }
}

void builtin_history()  {
    for (int i = 0; i < history_count; i++) {
        char history_line[CMD_BUF_SIZE + 20];
        snprintf(history_line, sizeof(history_line), "  %d  %s\n", i + 1, history_list[i]);
        write(STDOUT_FILENO, history_line, strlen(history_line));
    }
}

void execute_pipeline(char * line)  {
    char *pipe_cmds[MAX_PIPE_CMDS];
    int num_cmds = 0;

    char *pipe_token = strtok(line, "|");
    while (pipe_token != NULL && num_cmds < MAX_PIPE_CMDS)  {
        pipe_cmds[num_cmds++] = pipe_token;
        pipe_token = strtok(NULL, "|");
    }

    int pipe_fds[2]; //file descriptors for pipe
    int in_fd = STDIN_FILENO;
    pid_t child_pids[MAX_PIPE_CMDS];

    for (int i = 0; i < num_cmds; i++)  {
        int out_fd = STDOUT_FILENO;
        if (i < num_cmds - 1)   {
            if (pipe(pipe_fds) == -1)   {
                print_error_message("Error: Failed to create pipe.\n", NULL);
                return;
            }
            out_fd = pipe_fds[1];
        }
        char *args[MAX_ARGS];
        int n_args = 0;
        char *token = strtok(pipe_cmds[i]," \t\n");
        while(token != NULL && n_args < MAX_ARGS -1)    {
            args[n_args++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[n_args] = NULL;
        if (args[0] == NULL) {
            continue;
        }
        char * infile = NULL;
        char * outfile = NULL;
        for (int j = 0; j < n_args; j++)    {
            if (args[j] == NULL) continue;
            if (strcmp(args[j], "<") == 0)  {
                if (args[j + 1]) { 
                    infile = args[j + 1];
                    args[j] = NULL;
                }
            } else if(strcmp(args[j], ">") == 0)  {
                if (args[j + 1])    {
                    outfile = args[j + 1];
                    args[j] = NULL;
                }
            }
        }
        pid_t pid = fork();
        if(pid == -1)   {
            print_error_message("Error: Failed to fork process.\n", NULL);
            return;
        }
        //child process
        if (pid == 0)   {
            if (in_fd != STDIN_FILENO)  {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            if (out_fd != STDOUT_FILENO)    {
                dup2(out_fd, STDOUT_FILENO);
                close(out_fd);
            }
            if(i < num_cmds - 1)    {
                close(pipe_fds[0]);
            }

            if(infile)  {
                int fd_input = open(infile, O_RDONLY);
                if (fd_input == -1) {
                    print_error_message("Error: Failed to open input file: %s\n", infile);
                    exit(EXIT_FAILURE);
                }
                dup2(fd_input, STDIN_FILENO);
                close(fd_input);
            }

            if(outfile)   {
                int fd_output = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd_output == -1)    {
                    print_error_message("Error: Failed to open output file: %s\n", outfile);
                    exit(EXIT_FAILURE);
                }
                dup2(fd_output, STDOUT_FILENO);
                close(fd_output);
            }
            char * path_env = getenv("PATH");
            if (!path_env)  {
                print_error_message("Error : path environment variable is not configured.\n", NULL);
                exit(EXIT_FAILURE);
            }
            char path_copy[1024];
            strncpy(path_copy, path_env,sizeof(path_copy) -1);
            path_copy[sizeof(path_copy) -1] = '\0';
            char *dir = strtok(path_copy, ":");
            while (dir != NULL)     {
                char full_path[PATH_MAX];
                snprintf(full_path, sizeof(full_path), "%s/%s", dir, args[0]);
                execv(full_path, args);
                dir = strtok(NULL, ":");
            }
            print_error_message("Shell Error: Command '%s' not found.\n", args[0]);
            exit(EXIT_FAILURE);
        } else  {
            child_pids[i] = pid;
            if (in_fd != STDIN_FILENO)  {
                close(in_fd);
            }
            if(out_fd != STDOUT_FILENO) {
                close(out_fd);
            }
            if(i < num_cmds- 1) {
                in_fd = pipe_fds[0];
            }
        }
    }
    for (int i = 0;i < num_cmds;i++)    {
        int status;
        waitpid(child_pids[i], &status, 0);
    }
}


int main() {
    char line[CMD_BUF_SIZE];
    char *args[MAX_ARGS];
    while (1) {
        update_prompt();
        write(2, prompt_str, strlen(prompt_str));

        if (!fgets(line, sizeof(line), stdin)) {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) {
            continue;
        }

        add_to_history(line);

        if (strncmp(line, "PS1=", 4) == 0) {
            change_str_prompt(line + 4);
            continue;
        }
        if (strncmp(line, "PATH=", 5) == 0) {
            if (setenv("PATH", line + 5, 1) != 0) {
                const char *msg5 = "Error: Failed to set the PATH environment variable.\n";
                write(2, msg5, strlen(msg5));
            }
            continue;
        }
        int n_args = 0;
        char line_copy[CMD_BUF_SIZE];
        strcpy(line_copy, line);

        char *token = strtok(line, " \t\n");
        while (token != NULL && n_args < MAX_ARGS - 1){
            args[n_args++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[n_args] = NULL;
        if (args[0] == NULL) {
            continue;
        }
        if (strcmp(args[0], "exit") == 0){
            break;
        }
        if (strcmp(args[0], "cd") == 0){
            const char *target_dir = args[1] ? args[1] : getenv("HOME");
            if (target_dir && chdir(target_dir) != 0) {
                char error_buffer[PATH_MAX + 60];
                print_error_message("Shell Error: Failed to change directory to '%s'.\n", target_dir);
                write(2, error_buffer, strlen(error_buffer));
            }
            continue;
        }

        if (strcmp(args[0], "history") == 0){
            builtin_history();
            continue;
        }

        char *infile = NULL;
        char *outfile = NULL;
        
        execute_pipeline(line_copy);

    }
    const char *exit_msg = "exiting\n";
    write(1, exit_msg, strlen(exit_msg));
    return 0;

    for(int i = 0; i < history_count; i++){
        free(history_list[i]);
    }
}
