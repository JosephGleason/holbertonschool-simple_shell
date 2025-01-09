#include "shell.h"

/**
 * check_command_in_path - Checks if cmnd exists in PATH.
 * @command: The command to check.
 *
 * Return: Full path to the command if found, NULL otherwise.
 */
char *check_command_in_path(char *command)
{
	char *path_env = getenv("PATH");
	char *path_copy = strdup(path_env);
	char *dir = strtok(path_copy, ":");
	char *full_path;
	struct stat buffer;

	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		sprintf(full_path, "%s/%s", dir, command);

		if (stat(full_path, &buffer) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * fork_and_exec_command - Forks a process and executes the command.
 * @full_path: Full path to the command.
 * @args: Arguments for the command.
 */
void fork_and_exec_command(char *full_path, char **args)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execve(full_path, args, environ) == -1)
		{
			perror("execve failed");
			free(full_path);
			exit(1);
		}
	}
	else if (pid < 0)
	{
		perror("fork failed");
		free(full_path);
	}
}

/**
 * wait_for_child_process - Waits for the child process to finish execution.
 * @pid: The process ID of the child process.
 */
void wait_for_child_process(pid_t pid)
{
	int status;

	waitpid(pid, &status, 0);
}

/**
 * execute_command - Executes the command passed in the arguments.
 * @command: The command to execute.
 * @args: Arguments to pass to the command.
 *
 * Return: 1 if the command successfully, 0 if internal command.
 */
int execute_command(char *command, char **args)
{
	char *full_path = NULL;

	if (strcmp(command, "exit") == 0)
		exit(0);

	full_path = check_command_in_path(command);
	if (!full_path)
	{
		perror("Command not found");
		return (1);
	}

	fork_and_exec_command(full_path, args);

	wait_for_child_process(getpid());

	free(full_path);
	return (1);
}

