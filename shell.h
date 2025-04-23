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
void betty_matrix(int a[8][8]);
char *find_command(char *command);
char **input_handler(char *line);
int execute_shell(char **args, char *prog_name, int lineno);
int second_handler(char **args);
int handle_env(char **args);

#endif /* SHELL_H */

