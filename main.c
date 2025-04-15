#include "shell.h"

/**
 * main - Entry point for the simple shell program
 *
 * Return: 0 on success, or a non-zero value on error.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;
	char **args;
	char *cmd_path;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			display_prompt();

		read = getline(&line, &len, stdin);
		if (read > 0 && line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (read == -1)
		{
			free(line);
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(0);
		}

		args = input_handler(line);
		if (args == NULL || args[0] == NULL)
		{
			free(args);
			continue;
		}

		cmd_path = find_command(args[0]);
		if (cmd_path == NULL)
		{
			perror("command not found");
			free(args);
			continue;
		}

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
	}

	free(line);
	return (0);
}
