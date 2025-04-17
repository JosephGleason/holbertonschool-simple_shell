#include "shell.h"
/**
* main - Entry point
*
*
*
* Return: 0; or non-zero valued as an error if fails
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
