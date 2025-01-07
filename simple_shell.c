#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * display_prompt - Display shell prmpt if input is coming from terminal.
 *
 * This function checks if the shell is running interactively
 * and, if so, displays the prompt "#cisfun$ ".
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("#cisfun$ ");
		fflush(stdout);
	}
}

/**
 * check_command_in_path - Check if a comnd exists in directories in PATH.
 * @command: The command to check.
 *
 * Return: The full path to the command if found, NULL if not.
 */

char *check_command_in_path(char *command)
{
	char *path = NULL;
	char *path_copy;
	char *dir;
	char *full_path = malloc(1024);
	int i;

	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, F_OK) == 0)
		{
			return (command);
		}
		else
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", command);
			exit(127);
		}
	}

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;
			break;
		}
	}

	if (!path || path[0] == '\0') 
	{
		fprintf(stderr, "No valid directories in PATH\n");
		return NULL;
	}

	path_copy = strdup(path);

	if (full_path == NULL)
	{
		perror("malloc");
		free(path_copy);
		exit(1);
	}

	dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		snprintf(full_path, 1024, "%s/%s", dir, command);

		if (access(full_path, F_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		dir = strtok(NULL, ":");
	}

	free(path_copy);
	free(full_path);
	return (NULL);
}

/**
 * parse_input - Tokenizes the input string into an array of arguments.
 * @input: The input string to be parsed.
 *
 * This func splits input string by spaces, tabs & newlines into indiv args.
 *
 * Return: An array of arguments (strings).
 */
char **parse_input(char *input)
{
	char *current;
	char **args = malloc(1024 * sizeof(char *));
	int i = 0;

	if (args == NULL)
	{
		perror("malloc");
		exit(1);
	}


	current = strtok(input, " \t\n");
	while (current != NULL)
	{
		args[i++] = current;
		current = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	return (args);
}

/**
 * execute_command - Executes the command provided by the user.
 * @args: The array of arguments that represent the command to be executed.
 *
 * This function creates a child process to execute the command using execve().
 * If the command cannot be executed, it prints an error message.
 */
void execute_command(char **args)
{
	pid_t pid;
	char *command = args[0];
	char *full_path = NULL;

	/* check if command absolute or relative path */
	if (command[0] == '/' || command[0] == '.')
	{
		/*if command is full path, chk if exists */
		if (access(command, F_OK) == 0)
		{
			full_path = strdup(command);  /* If command exists, use it directly */
		}
		else
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", command);
			exit(127);
		}
	}
	else
	{
		/* If command is not full path, srch in PATH */
		full_path = check_command_in_path(command);
	}

	/* If command found, execute */
	if (full_path != NULL)
	{
		pid = fork(); /* create new process */

		if (pid == 0)
		{
			if (execve(full_path, args, environ) == -1)
			{
				perror("./shell");
				exit(1);
			}
		}
		else if (pid < 0)
		{
			perror("fork");
		}
		else
		{
			wait(NULL);
		}

		free(full_path);
	}
	else
	{
		fprintf(stderr, "%s: command not found: %s\n", args[0], args[0]);
		exit(127);
	}
}

/**
 * handle_input - Processes user input and executes the command.
 * @input: The user input string.
 *
 * This function parses the input, checks if the user wants to exit,
 * and executes the command.
 *
 * Return: 0 if "exit" is typed, otherwise returns 1.
 */
int handle_input(char *input)
{
	char **args = parse_input(input);

	if (args[0] != NULL && strcmp(args[0], "exit") == 0)
	{
		free(args);
		return (0);
	}

	if (args[0] != NULL)
	{
		execute_command(args);
	}

	free(args);
	return (1);
}

/**
 * main - Main entry point of the shell program.
 *
 * This function handles the main loop of the shell, displaying the prompt,
 * reading input, and processing commands until the user types "exit".
 * Return: 0 if shell exits successfully, or other value if there is an error.
 */
int main(void)
{
	char *input = NULL;
	size_t len = 0;
	int run = 1;

	while (run)
	{
		display_prompt();

		if (getline(&input, &len, stdin) == -1)
		{
			run = 0;
			continue;
		}


		input[strcspn(input, "\n")] = '\0';

		if (input[0] == '\0')
			continue;
		run = handle_input(input);
	}

	free(input);
	return (0);
}

