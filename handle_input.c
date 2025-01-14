#include "shell.h"

void execute_from_path(char *prog_name, char *cmd, char **args)
{
	char *cmd_path, *path, *dir, path_copy[1024];
	struct stat st;

	path = get_path_env();
	if (!path || !*path)
		path = "/bin:/usr/bin";

	strcpy(path_copy, path);
	dir = strtok(path_copy, ":");

	while (dir)
	{
		cmd_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (!cmd_path)
			return;

		sprintf(cmd_path, "%s/%s", dir, cmd);
		if (stat(cmd_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			pid_t pid = fork();
			if (pid == 0)
			{
				execve(cmd_path, args, environ);
				perror("execve"); /* Execve failed */
				free(cmd_path);
				exit(127); /* Command not found */
			}
			else if (pid > 0)
			{
				int status;
				waitpid(pid, &status, 0);
				if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
				{
					printf("OK\n");
					fflush(stdout);
				}
				free(cmd_path);
				return;
			}
			else
			{
				perror("fork");
			}
		}
		free(cmd_path);
		dir = strtok(NULL, ":");
	}
	fprintf(stderr, "%s: %s: command not found\n", prog_name, cmd);
}

