#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * Simple Shell Program
 *
 * This is a basic shell program that simulates the behavior of a Unix shell.
 * The shell reads input from the user, parses the input into command and 
 * arguments, and executes the corresponding command. If the command is not 
 * found in the directories listed in the PATH environment variable or is 
 * invalid, an error message is displayed. The shell also supports exit functionality.
 *
 * Features:
 * - Display a prompt (`#cisfun$ `) when the shell is interactive.
 * - Parse the input into commands and arguments.
 * - Check if the command is an absolute path or search for it in directories listed in PATH.
 * - Handle basic commands and execute them using `execve`.
 * - Handle the `exit` command to terminate the shell.
 * - Error handling for invalid commands.
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
 * check_command_in_path - Check if a command exists in directories in PATH.
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

	if (!full_path)
	{
		perror("malloc");
		exit(1);
	}

	/* Check if the command is an absolute or relative path */
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

	/* Get the value of PATH from the environment */
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;
			break;
		}
	}

	if (path == NULL)
	{
		/* Fallback PATH */
		path = "/usr/bin:/bin:/usr/local/bin";
	}

	/* Handle the case where PATH is empty or not set */
	if (!path || path[0] == '\0') 
	{
		fprintf(stderr, "No valid directories in PATH\n");
		return NULL;
	}

	path_copy = strdup(path);

	/* Check for memory allocation failure */
	if (!path_copy)
	{
		perror("malloc");
		free(full_path);
		exit(1);
	}

	dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		/* Build the full path */
		snprintf(full_path, 1024, "%s/%s", dir, command);

		/* Check if snprintf was successful */
		if (strlen(full_path) >= 1024)
		{
			fprintf(stderr, "Path too long: %s/%s\n", dir, command);
			free(path_copy);
			free(full_path);
			return NULL;
		}

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
 * Return: An array of arguments (strings).
 */
char **parse_input(char *input)
{
	char *current;
	char **args = malloc(1024 * sizeof(char *));
	int i = 0;

	if (!args)
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
 */
void execute_command(char **args)
{
	pid_t pid;
	char *command = args[0];
	char *full_path = NULL;

	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, F_OK) == 0)
		{
			full_path = strdup(command);  
		}
		else
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", command);
			exit(127);
		}
	}
	else
	{
		full_path = check_command_in_path(command);
	}

	if (full_path != NULL)
	{
		pid = fork();

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
		if (strncmp(args[0], "export", 6) == 0)
		{
			handle_export(args[0]);
			free(args);
			return(1);
		}
		execute_command(args);
	}

	free(args);
	return (1);
}

/**
 * main - Main entry point of the shell program.
 *
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

