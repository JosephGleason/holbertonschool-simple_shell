#include "shell.h"

/**
 * find_command - Finds the full path of a command in PATH
 * @command: The command to search for (e.g. "ls")
 *
 * Return: Full path to the command if found (must be freed),
 *         or NULL if not found
 */
char *find_command(char *command)
{
	char *path_env = NULL, *path_copy, *token;
	char full_path[1024];
	int found = 0, i;

	/* If the command contains a slash, assume it’s a path already */
	if (strchr(command, '/') != NULL)
		return (strdup(command));

	for (i = 0; environ[i]; i++)/*Manually locate the PATH entry in environ[]*/
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path_env = environ[i] + 5;
			break;
		}
	}
	if (path_env == NULL)
		return (NULL);

	path_copy = strdup(path_env);/*Make a writable copy*/
	if (path_copy == NULL)
		return (NULL);
	token = strtok(path_copy, ":");

	while (token != NULL)
	{   /*Build full_path with sprintf (allowed)*/
		sprintf(full_path, "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
		{
			found = 1;
			break;
		}
		token = strtok(NULL, ":");
	}
	free(path_copy);

	if (found)
		return (strdup(full_path));
	return (NULL);
}
