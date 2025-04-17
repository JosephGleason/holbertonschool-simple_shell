#include "shell.h"
/**
* execute_shell - Handles the PATH to execute shell
*
*
*
* Return: 0
*/
int execute_shell(void)
{
	char *line = NULL;
	pid_t pid;
	int status;
	char **args = NULL;
	char *cmd_path = NULL;

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
		free(args);
	}

	free(line);
	return (0);
}
