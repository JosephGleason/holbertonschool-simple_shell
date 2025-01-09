#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

extern char **environ;

int execute_command(char *command, char **args);
int handle_input(char *input);
char **parse_input(char *input);
void display_prompt(void);
char *check_command_in_path(char *command);
void fork_and_exec_command(char *full_path, char **args);
void wait_for_child_process(pid_t pid);

#endif /* SHELL_H */

