
#include "shell.h"

/**
 * main - Entry point for the simple shell program
 *
 * Return: 0 on success, or a non-zero value on error.
 */
int main(void)
{
	char *line = NULL;/*ptr to a char buffer set to NULL*/
	size_t len = 0;/*size of buffer init to 0, getline will set it properly*/
	ssize_t read;/*number of chars read from user input*/

	while (1)/*infinite loop*/
	{
		display_prompt();/*gotta show dat prompt baby*/

		read = getline(&line, &len, stdin);/*read input from user*/
		if (read == -1)/*if user ctrl+d (EOF) or exit shell*/
		{
			free(line);
			write(STDOUT_FILENO, "\n", 1);/*prints newline char to terminal*/
			exit(0);
		}
		if (line[read - 1] == '\n')/*erase '\n' from terminal*/
		{
			line[read - 1] = '\0';
		}

		write(STDOUT_FILENO, line, read - 1);
		write(STDOUT_FILENO, "\n", 1);/*adds new line for formatting*/
	}
	free(line);
	return (0);
}
