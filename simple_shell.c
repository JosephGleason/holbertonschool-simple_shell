#include "shell.h"

/**
 * display_prompt - Displays the shell prompt if input is from a terminal.
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO)) /* Check if input is from a terminal */
	{
		write(STDOUT_FILENO, "$ ", 2); /* Display prompt */
	}
}

/**
 * main - Entry point of the shell program.
 *
 * Return: 0 on success, or exit with an error code.
 */
int main(void)
{
	char *input_line = NULL;  /* Pointer for input line */
	size_t len = 0;          /* Size for getline */
	ssize_t read;            /* Read return value */
	char **args;             /* Array for parsed arguments */
	int i;                   /* Loop index */
	int run = 1;             /* Flag to control the main loop */

	while (run)
	{
		display_prompt(); /* Show prompt for interactive mode */

		/* Read input using getline */
		read = getline(&input_line, &len, stdin);
		if (read == -1) /* EOF or error */
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1); /* Print newline for EOF */
			break;
		}

		input_line[strcspn(input_line, "\n")] = '\0'; /* Remove newline character */

		if (input_line[0] == '\0')
			continue; /* Skip empty input */

		if (strcmp(input_line, "exit") == 0) /* Handle "exit" command */
		{
			free(input_line);
			exit(0);
		}

		args = parse_input(input_line); /* Parse input into arguments */

		if (args != NULL && args[0] != NULL) /* Ensure arguments are valid */
		{
			execute_from_path("simple_shell", args[0], args); /* Execute command */
		}

		/* Free memory allocated for arguments */
		for (i = 0; args[i] != NULL; i++)
		{
			free(args[i]);
		}
		free(args);
	}

	free(input_line); /* Free input buffer before exiting */
	return (0);
}

