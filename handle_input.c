#include "shell.h"  /* Include shell.h for necessary declarations */

void execute_from_path(char *cmd, char **args)
{
	char *cmd_path;
	struct stat st;
	char *path;          /* Declare path here */
	char path_copy[1024]; /* Declare path_copy here */
	char *dir;          /* Declare dir here */

	/* Check if the command is an absolute path */
	if (cmd[0] == '/')
	{
		/* Check if the command is executable */
		if (stat(cmd, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			pid_t pid = fork();
			if (pid == 0)  /* Child process */
			{
				if (execve(cmd, args, environ) == -1)  /* If execve fails */
				{
					perror("execve");  /* Print the error message */
					exit(1);  /* Exit child process with failure */
				}
			}
			else if (pid > 0)  /* Parent process */
			{
				waitpid(pid, NULL, 0);  /* Wait for the child process to finish */
				return;
			}
			else  /* Fork failed */
			{
				perror("fork");
				return;
			}
		}
		else
		{
			fprintf(stderr, "%s: command not found\n", cmd);  /* Command not found message */
			return;
		}
	}

	/* If not an absolute path, proceed with searching in PATH */
	path = get_path_env();  /* Get the PATH environment variable */
	if (path == NULL || strlen(path) == 0)
	{
		path = "/bin:/usr/bin";  /* Fallback to default directories */
	}

	strcpy(path_copy, path);  /* Copy path to avoid modifying the literal */
	dir = strtok(path_copy, ":");  /* Tokenize the path */

	while (dir)
	{
		cmd_path = malloc(strlen(dir) + strlen(cmd) + 2);  /* Allocate memory for cmd path */
		if (!cmd_path)
			return;

		strcpy(cmd_path, dir);
		strcat(cmd_path, "/");
		strcat(cmd_path, cmd);

		if (stat(cmd_path, &st) == 0 && (st.st_mode & S_IXUSR))  /* Check if file is executable */
		{
			pid_t pid = fork();
			if (pid == 0)  /* Child process */
			{
				if (execve(cmd_path, args, environ) == -1)  /* If execve fails */
				{
					perror("execve");  /* Print the error message */
					free(cmd_path);  /* Free memory before exiting */
					exit(1);  /* Exit child process with failure */
				}
			}
			else if (pid > 0)  /* Parent process */
			{
				waitpid(pid, NULL, 0);  /* Wait for the child process to finish */
				free(cmd_path);  /* Free memory */
				return;
			}
			else  /* Fork failed */
			{
				perror("fork");
				free(cmd_path);  /* Free memory before returning */
				return;
			}
		}

		free(cmd_path);  /* Free memory before moving to the next directory */
		dir = strtok(NULL, ":");
	}

	fprintf(stderr, "%s: command not found\n", cmd);  /* Command not found message */
}
