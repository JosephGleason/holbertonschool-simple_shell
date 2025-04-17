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
int execute_shell(void);
int second_handler(char **args);


#endif /* SHELL_H */

