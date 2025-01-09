#include "shell.h"

/**
 * construct_full_path - Constructs the full path for a command
 * @dir: The directory to prepend
 * @command: The command to append
 *
 * Return: The full path as a string, or NULL on failure
 */
char *construct_full_path(char *dir, char *command)
{
	char *full_path = malloc(strlen(dir) + strlen(command) + 2);

	if (full_path == NULL)
		return (NULL);

	sprintf(full_path, "%s/%s", dir, command);
	return (full_path);
}

/**
 * is_command_executable - Checks if the command is executable
 * @full_path: The full path of the command
 *
 * Return: 1 if executable, 0 otherwise
 */
int is_command_executable(char *full_path)
{
	struct stat buffer;

	if (stat(full_path, &buffer) == 0)
		return (1);

	return (0);
}

/**
 * get_path_env - Retrieves the PATH environment variable
 *
 * Return: A pointer to the PATH string, or NULL if not found
 */
char *get_path_env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
	}

	return (NULL);
}

/**
 * check_command_in_path - Searches for a command in directories listed in PATH
 * @command: The command to search for
 *
 * Return: The full path to the command if found, NULL otherwise
 */
char *check_command_in_path(char *command)
{
	char *path_env, *path_copy, *dir, *full_path;

	path_env = get_path_env();
	if (path_env == NULL)
		return (NULL);

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = construct_full_path(dir, command);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		if (is_command_executable(full_path))
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * wait_for_child_process - Waits for the child process to finish
 * @pid: The process ID of the child process.
 *
 * This function waits for the child process identified by `pid` to terminate.
 * It uses the `waitpid` system call and checks if the child process terminated
 * successfully. If the child exited normally, the exit status is printed.
 */
void wait_for_child_process(pid_t pid)
{
	int status;

	/* Wait for the child process */
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
	}
	else
	{
		/* Optionally check the exit status of the child process */
		if (WIFEXITED(status))
		{
			printf("Child exited with status %d\n", WEXITSTATUS(status));
		}
	}
}
