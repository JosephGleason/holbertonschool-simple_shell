#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

extern char **environ;

/* Function declarations */
void execute_from_path(char *prog_name, char *command, char **args);
char **parse_input(char *input);
void display_prompt(void);
char *check_command_in_path(char *command);
char *construct_full_path(char *dir, char *command);
int is_command_executable(char *full_path);
void fork_and_exec_command(char *full_path, char **args);
void wait_for_child_process(pid_t pid);
char *validate_command(char *command);
void fork_and_execute(char *full_path, char **args);
char *get_path_env(void);

#endif /* SHELL_H */
