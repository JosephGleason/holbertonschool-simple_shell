#include "shell.h"

/**
 * execute_shell - Handles the PATH to execute shell
 * @args:      array of strings with commands and arguments
 * @prog_name: holds program’s name
 * @lineno:    line number from input
 *
 * Return: exit status, 127 if not found, 1 on error
 */
int execute_shell(char **args, char *prog_name, int lineno)
{
	pid_t pid;
	int   status;
	char *cmd_path;

	/* find the full path of the command */
	cmd_path = find_command(args[0]);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, lineno, args[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free(cmd_path);
		exit(1);
	}

	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror("execve failed");
			free(cmd_path);
			exit(1);
		}
	}
	else
	{
		wait(&status);
		free(cmd_path);
	}

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
