#include "shell.h"
/**
 * execute_shell - Handles the PATH to execute shell
 *
 *
 *
 * Return: 0
 */
int execute_shell(char **args)
{
	char *line = NULL;
	pid_t pid;
	int status;
	char *cmd_path;

	/* find the full path of the command */
	cmd_path = find_command(args[0]);
	if (cmd_path == NULL)
		return (perror(args[0]), 1);

	pid = fork();

	if (pid == -1)
	{
		perror("fork failed");
		free(line);
		free(cmd_path);
		free(args);
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror("execve failed");
			free(cmd_path);
			free(args);
			exit(1);
		}
	}
	else
	{
		wait(&status);
		free(cmd_path);
	}

	free(line);
	return (0);
}
