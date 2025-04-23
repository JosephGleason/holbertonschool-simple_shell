#include "shell.h"
#include <string.h>

/**
 * find_command - Finds the full path of a command in PATH
 * @command: The command to search for (e.g. "ls")
 *
 * Return: Full path to the command if found (must be freed),
 *         or NULL if not found
 */
char *find_command(char *command)
{
	char *path_env, *path_copy, *token;
	char full_path[1024];
	int found = 0;

	if (strchr(command, '/') != NULL)
		return (strdup(command)); /* Command already has a path */

	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	token = strtok(path_copy, ":");

	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
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
