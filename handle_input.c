#include "shell.h"

/**
 * validate_command - Validates a command's existence, size, and permissions
 * @command: The command to validate
 *
 * Return: Full path to the command if valid, NULL otherwise
 */
char *validate_command(char *command)
{
	char *full_path = check_command_in_path(command);
	struct stat st;

	if (full_path == NULL || stat(full_path, &st) != 0)
	{
		fprintf(stderr, "%s: command not found\n", command);
		free(full_path);
		return (NULL);
	}

	if (st.st_size == 0)
	{
		fprintf(stderr, "%s: File is empty\n", command);
		free(full_path);
		return (NULL);
	}

	if (access(full_path, X_OK) != 0)
	{
		fprintf(stderr, "%s: Permission denied or not executable\n", command);
		free(full_path);
		return (NULL);
	}

	return (full_path);
}

/**
 * fork_and_execute - Forks a process and executes a command
 * @full_path: Full path to the command
 * @args: The arguments for the command
 */
void fork_and_execute(char *full_path, char **args)
{
	pid_t pid = fork();

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
 * execute_from_path - Executes a command found in the PATH
 * @args: The arguments for the command
 * @command: The command to execute
 */
void execute_from_path(char *command, char **args)
{
	char *full_path = validate_command(command);

	if (full_path != NULL)
	{
		fork_and_execute(full_path, args);
	}
}

