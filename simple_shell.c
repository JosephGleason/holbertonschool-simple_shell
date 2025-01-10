#include "shell.h"

/**
 * display_prompt - Displays the shell prompt if input is from a terminal.
 */
void display_prompt(void)
{
	/* Only display the prompt if running interactively (from terminal) */
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$ ", 2); /* Display prompt using write */
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
	char **args;


	while (run)
	{
		display_prompt(); /* Show prompt for interactive mode */

		/* Handle input, considering both interactive and non-interactive modes */
		if (isatty(STDIN_FILENO))
		{
			if (getline(&input, &len, stdin) == -1)
			{

				break; /* EOF or error, exit loop */

			}
		}
		else
		{
			/* For non-interactive mode (e.g., sandbox), continue reading input */
			if (getline(&input, &len, stdin) == -1)
			{
				break; /* EOF or error, exit loop */
			}
		}

		input[strcspn(input, "\n")] = '\0'; /* Remove the newline character */

		if (input[0] == '\0')
			continue; /* Skip empty input */

		/* Handle the exit command */
		if (strcmp(input, "exit") == 0)
		{
			free(input);  /* Free input buffer */
			exit(0);      /* Exit the shell */
		}

		args = parse_input(input); /* Parse the input into arguments */

		/* Ensure args is not NULL */
		if (args != NULL && args[0] != NULL)
		{
			execute_from_path(args[0], args); /* Call execute_from_path for execution */
		}

		/* Free memory for arguments, assuming each element in args was malloced */
		if (args != NULL)
		{
			free(args);
		}
	}

	free(input); /* Free input buffer before exit */
	return (0);
}

