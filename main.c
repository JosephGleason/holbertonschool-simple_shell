#include "shell.h"

/**
 * handle_builtins - handle blank, env or exit commands
 * @args:     tokenized input array
 * @line_p:   address of the raw input buffer
 * @status_p: pointer to current status
 *
 * Return: 1 if a builtin ran (and main should continue), 0 otherwise
 */
static int handle_builtins(char **args, char **line_p, int *status_p)
{
	if (args[0] == NULL)             /* blank line (newline only) */
	{
		free(args);
		return (1);
	}
	if (strcmp(args[0], "env") == 0)
	{
		*status_p = handle_env();
		free(args);
		return (1);
	}
	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(*line_p);
		exit(*status_p);
	}
	return (0);
}

/**
 * main - Entry point for the simple shell program
 * @argc: argument count (unused)
 * @argv: array of strings: program name and arguments
 *
 * Return: 0 on success, or non‐zero on error
 */
int main(int argc, char *argv[])
{
	char    *line   = NULL;
	size_t   len    = 0;
	ssize_t  read;
	char   **args;
	int      lineno = 0;
	int      status = 0;

	(void)argc;
	while (1)
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
		if (handle_builtins(args, &line, &status))  /* blank/env/exit */
			continue;

		status = execute_shell(args, argv[0], lineno);
		free(args);
	}
	free(line);
	return (0);
}

