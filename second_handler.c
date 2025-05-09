#include "shell.h"
/**
* second_handler - Prints error message for NULL path
* @args: argument
*
* Return: Prints message error for NULL path, 0
*/
int second_handler(char **args)
{
	char *line = NULL;
	char *cmd_path;

	cmd_path = find_command(args[0]);
	if (cmd_path == NULL)
	{
		perror("command not found");
		free(args);
	}
	free(line);
	return (0);
}
