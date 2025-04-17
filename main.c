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
	char **args;

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

	}

	free(line);
	return (0);
}
