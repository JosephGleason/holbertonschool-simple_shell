#include "shell.h"

/**
 * display_prompt - Displays the shell prompt if input is from a terminal.
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$ ", 2);
	}
}

/**
 * main - Entry point of the shell program.
 *
 * Return: 0 on success, or exit with an error code.
 */
int main(void)
{
	char *input = NULL;
	size_t len = 0;
	int run = 1;

	while (run)
	{
		display_prompt();

		if (getline(&input, &len, stdin) == -1)
		{
			run = 0;
			continue;
		}

		input[strcspn(input, "\n")] = '\0';

		if (input[0] == '\0')
			continue;

		run = handle_input(input);
	}

	free(input);
	return (0);
}

