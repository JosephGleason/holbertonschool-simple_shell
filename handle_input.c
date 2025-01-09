#include "shell.h"

/**
 * execute_from_path - Executes a command found in the PATH
 * @args: The arguments for the command
 * @command: The command to execute
 */
void execute_from_path(char *command, char **args)
{
	char *full_path = check_command_in_path(command);
	pid_t pid;

	if (full_path == NULL)
	{
		fprintf(stderr, "%s: command not found\n", command);
		return;
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(full_path);
		return;
	}
	if (pid == 0)
	{
		/* Child process: Execute the command */
		if (execve(full_path, args, environ) == -1)
		{
			perror("execve");
			free(full_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process: Wait for the child to finish */
		wait_for_child_process(pid);
	}

	free(full_path);
}

/**
 * handle_input - Handles the input received from the user
 * @input: The user input to be processed.
 *
 * Return: 1 if the shell should continue running, 0 if it should exit.
 */
int handle_input(char *input)
{
	char **args;

	args = parse_input(input);
	if (args[0] != NULL && strcmp(args[0], "exit") == 0)
	{
		free(args);
		return (0);
	}

	if (args[0] != NULL)
	{
		execute_from_path(args[0], args);
	}

	free(args);
	return (1);
}

