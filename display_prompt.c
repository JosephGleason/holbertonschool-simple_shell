#include "shell.h"

/**
 * display_prompt - Prints the shell prompt to stdout
 *
 * Description: This function writes the "$ " prompt
 * directly to standard output using the write system call.
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);/* Show prompt only in interactive mode */
}
