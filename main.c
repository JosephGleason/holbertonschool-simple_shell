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

	while (1)/*infinite loop*/
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
		if (args == NULL)            /* malloc/realloc failure */
			continue;

		if (args[0] == NULL)         /* blank line (newline only) */
		{
			free(args);
			continue;
		}
		if (strcmp(args[0], "exit") == 0)
		{
			free(args);
			free(line);
			exit(0);
		}
		/* — ▶ Execute the command ▶ — */
		execute_shell(args);
		free(args);
	}

	free(line);
	return (0);
}
