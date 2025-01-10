#include "shell.h"

void execute_from_path(char *cmd, char **args)
{
	char *path = "/bin:/usr/bin";  /* Define a default path manually */
	char *dir, *cmd_path;
	struct stat st;

	dir = strtok(path, ":");
	while (dir)
	{
		cmd_path = malloc(strlen(dir) + strlen(cmd) + 2);  /* Allocate memory for cmd path */
		if (!cmd_path)
			return;

		strcpy(cmd_path, dir);
		strcat(cmd_path, "/");
		strcat(cmd_path, cmd);

		if (stat(cmd_path, &st) == 0 && st.st_mode & S_IXUSR)  /* Check if file is executable */
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
				wait(NULL);  /* Wait for the child process to finish */
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

