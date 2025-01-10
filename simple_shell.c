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
	char **args;

	while (run)
	{
		display_prompt();

		if (getline(&input, &len, stdin) == -1)
		{
			if (input == NULL)  /* Check if getline returns NULL*/
			{
				break;  /* EOF or error, exit loop*/
			}
			perror("getline");
			run = 0;
			continue;
		}

		input[strcspn(input, "\n")] = '\0';

		if (input[0] == '\0')
			continue;

		args = parse_input(input);  /* Parse the input into arguments*/
		if (args[0] != NULL)
		{
			if (strcmp(args[0], "exit") == 0)  /* Handle exit command*/
			{
				free(args);
				free(input);
				exit(0);  /* Or return to exit the shell*/
			}
			execute_from_path(args[0], args);  /* Call execute_from_path*/
		}
		free(args);  /* Don't forget to free the memory*/

	}

	free(input);
	return (0);
}

