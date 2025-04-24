#include "shell.h"
/**
 * main - Entry point for the simple shell program
 * @argc: argument count (number of elements in argv)
 * @argv: array of strings: program name and arguments
 *
 * Return: 0 on success, or a non-zero value on error.
 */
int main(int argc, char *argv[])
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;
	int lineno = 0;
	int status = 0;

	(void)argc;

	while (1)/*infinite loop*/
	{
		lineno++;

		if (isatty(STDIN_FILENO))
			display_prompt();

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			free(line);

			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(status);
		}

		if (read > 0 && line[read - 1] == '\n')
			line[read - 1] = '\0';

		args = input_handler(line);
		if (args == NULL)            /* malloc/realloc failure */
			continue;

		if (args[0] == NULL)         /* blank line (newline only) */
		{
			free(args);
			continue;
		}

		if (strcmp(args[0], "env") == 0)
		{
			status = handle_env();
			free(args);
			continue;
		}

		if (strcmp(args[0], "exit") == 0)
		{
			free(args);
			free(line);
			exit(status);
		}

		/* — ▶ Execute the command ▶ — */
		status = execute_shell(args, argv[0], lineno);
		free(args);
	}

	free(line);
	return (0);
}
