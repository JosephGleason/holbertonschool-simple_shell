#include "shell.h"

/**
 * parse_input - Tokenizes a string into arguments.
 * @input: Input string to be tokenized.
 *
 * Return: An array of strings (arguments) or NULL on failure.
 */
char **parse_input(char *input)
{
	char *current;
	char **args = malloc(1024 * sizeof(char *)); /* Allocate memory for arguments */
	int i = 0;

	if (!args) /* Check memory allocation */
	{
		perror("malloc");
		exit(1);
	}

	current = strtok(input, " \t\n"); /* Tokenize input */
	while (current != NULL)
	{
		args[i] = strdup(current); /* Duplicate token into args */
		if (!args[i]) /* Check memory allocation */
		{
			perror("strdup");
			exit(1);
		}
		i++;
		current = strtok(NULL, " \t\n");
	}
	args[i] = NULL; /* Null-terminate the array */

	return (args);
}

