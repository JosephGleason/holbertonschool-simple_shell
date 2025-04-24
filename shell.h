#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

/* Function Declarations */
void display_prompt(void);
char *find_command(char *command);
char **input_handler(char *line);
int execute_shell(char **args, char *prog_name, int lineno);
int second_handler(char **args);
int handle_env(void);
int handle_builtins(char **args, char **line_p, int *status_p);

#endif /* SHELL_H */

