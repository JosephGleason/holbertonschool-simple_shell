#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(void)
{
	char *input = NULL;  /* Pointer for user input */
	size_t len = 0;      /* Variable to hold the size of the input buffer */
	pid_t pid;	
	int i = 0;
	char *args[1024];
	char *current;

	while (1) /* Infinite loop to display prompt repeatedly */
	{
		if (isatty(STDIN_FILENO))
		{
			printf("#cisfun$ "); /* Print the prompt */
		}
		if (getline(&input, &len, stdin) == -1)
		{	
			if (feof(stdin))
			{
				break;
			}
			else
			{
				printf("error detected...\n"); /* Handle Ctrl+D (EOF): Exit gracefully */
				break;
			}

		}

		i = 0;
		current = input;
		/* Manually split input into command and arguments */
		while (*current != '\0')  /* Loop through each character */
		{
			/* Skip leading spaces */
			if (*current == ' ' || *current == '\t')
			{
				current++;
				continue;
			}

			/* Set the beginning of the argument */
			args[i] = current;

			/* Move through the argument (until a space or null terminator) */
			while (*current != ' ' && *current != '\0' && *current != '\t')
			{
				current++;
			}

			/* Null terminate the argument */
			if (*current != '\0')
			{
				*current = '\0';
				current++;  /* Move to the next character */
			}

			i++;  /* Move to the next argument */
		}

		args[i] = NULL;  /* Terminate the arguments array with NULL for execve */

		/* Handle exit command */
		if (strcmp(args[0], "exit") == 0)
		{
			break; /* Exit the shell */
		}

		/* Fork a child process to execute the command */
		pid = fork();
		if (pid == 0)  /* Child process */
		{
			if (execve(args[0], args, environ) == -1)  /* Try executing the command */
			{
				perror("./shell");  /* Print error if command not found */
				exit(1);  /* Exit the child process if execve fails */
			}
		}
		else if (pid < 0)  /* Fork failed */
		{
			perror("fork");
		}
		else  /* Parent process */
		{
			wait(NULL);  /* Wait for child process to finish */
		}
	}

	free(input); /* Free the dynamically allocated memory */
	return (0);	

}
