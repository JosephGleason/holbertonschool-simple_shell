#include "shell.h"

/**
 * parse_input - Parses the user input into commands and arguments
 * @input: The raw input string from the user.
 *
 * This function processes the user input, separates it into individual
 * commands and arguments, and returns the parsed data.
 *
 * Return: A pointer to an array of strings containing commands and arguments.
 */
char **parse_input(char *input)
{
	char *current;
	char **args = malloc(1024 * sizeof(char *));
	int i = 0;

	if (!args)
	{
		perror("malloc");
		exit(1);
	}

	current = strtok(input, " \t\n");
	while (current != NULL)
	{
		args[i++] = current;
		current = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	return (args);
}

