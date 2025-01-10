#include "shell.h"

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

