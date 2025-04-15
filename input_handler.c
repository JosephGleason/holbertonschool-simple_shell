#include "shell.h"

/**
 * input_handler - Parses input into an array of arguments
 * @line: The raw input string from the user
 *
 * Return: NULL-terminated array of strings (must be freed)
 */
char **input_handler(char *line)
{
	char **args;
	char *word;
	int i = 0;
	int bufsize = 64;

	args = malloc(sizeof(char *) * bufsize);
	if (args == NULL)
		return (NULL);

	word = strtok(line, " ");
	while (word != NULL)
	{
		args[i] = word;
		i++;

		if (i >= bufsize)
		{
			bufsize += 64;
			args = realloc(args, sizeof(char *) * bufsize);
			if (args == NULL)
				return (NULL);
		}

		word = strtok(NULL, " ");
	}
	args[i] = NULL;

	return (args);
}
