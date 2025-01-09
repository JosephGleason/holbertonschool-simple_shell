#include "shell.h"

/**
 * handle_input - Handles the input received from the user
 * @input: The user input to be processed.
 *
 * This function processes the user's input, executes the corresponding
 * command, and returns 1 to continue running or 0 to exit the shell.
 *
 * Return: 1 if the shell should continue running, 0 if it should exit.
 */
int handle_input(char *input)
{
	char **args = parse_input(input);

	if (args[0] != NULL && strcmp(args[0], "exit") == 0)
	{
		free(args);
		return (0);
	}

	if (args[0] != NULL)
	{
		execute_command(args[0], args);
	}

	free(args);
	return (1);
}

