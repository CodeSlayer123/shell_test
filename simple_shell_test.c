#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
char **splitter(char fun[]);
int execArgs(char **argv);

int main(void)
{
	size_t bufsize = 200000;
	char *buffer;
	char **argv;
	int length;
	struct stat st;

	buffer = malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		return (-1);
	}
	do {
		printf("#cisnotfun$ ");
		length = getline(&buffer, &bufsize, stdin);

		if (length == EOF)
		{
			putchar('\n');
			free(buffer);
			exit(-1);
		}

		if (strcmp(buffer, "exit\n") == 0)
		{
			free(buffer);
			exit(0);
		}
		if (buffer[strlen(buffer) - 1] == '\0')
		{
			buffer[strlen(buffer) - 1] = '\0';
		}
		argv = splitter(buffer);

		if (buffer[0] == '.' && buffer[1] == '/')
		{
			if (access(argv[0], F_OK) == 0)
			{
				execArgs(argv);
			}
			else
			{
				printf("%s: not found\n", argv[0]);
			}
		}
		else
		{
			if (stat(argv[0], &st) == 0)
			{
				execArgs(argv);
			}
			else
			{
				printf("%s: not found\n", argv[0]);
			}
		}

	} while (length != -1);

	free(buffer);
	return (0);
}
int execArgs(char **argv)
{
	int status;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return (-1);
	}
	if (pid == 0)
	{
		execve(argv[0], argv, NULL);
	}
	else
	{
		wait(&status);
	}
	return (0);
}
int checkBuiltIn(char **parsed)
{
	return (0);
}
