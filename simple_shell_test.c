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
int executePath(char *execPath, char **argv);
char **_getPath(void);
char *_getenv(const char *name);

int main(void)
{
	size_t bufsize = 200000;
	char *buffer;
	char **argv;
	int length;
	struct stat st;
	char **path = _getPath();
	char *execPath = malloc(sizeof(char) * 1024);
	int i;
	char *pwd = getcwd(pwd, bufsize), *hd = getcwd(pwd, bufsize);
	int cd;

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

		if (buffer[strlen(buffer) - 1] == '\n')
		{
			buffer[strlen(buffer) - 1] = '\0';
		}
		argv = splitter(buffer);
		if (strcmp(argv[0], "exit") == 0)
		{
			printf("exit\n");
			if (!argv[1] || (argv[1][0] >= '0' && argv[1][0] <= '9'))
			{
				free(buffer);
				exit(0);
			}
			else
			{
				printf("./hsh: exit: ");
				printf("%s: numeric argument required\n", argv[1]);
				free(buffer);
				exit(0);
			}
		}
		if (strcmp(argv[0], "cd") == 0)
		{
			cd = chdir(argv[1]);
			if (!argv[1])
				cd = chdir(hd);
			if (cd != 0)
			{
				printf("./hsh: cd: %s: No such file or directory\n", argv[1]);
			}
			pwd = getcwd(pwd, bufsize);
			continue;
		}
		if (strcmp(argv[0], "pwd") == 0)
		{
			printf("%s\n", pwd);
			continue;
		}

		if (strchr(argv[0], '/'))
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
		else
		{
			for (i = 0; path[i] != NULL; i++)
			{
				strcpy(execPath, path[i]);
				strcat(execPath, "/");
				strcat(execPath, argv[0]);
				if (stat(execPath, &st) == 0)
				{
					executePath(execPath, argv);
					break;
				}
			}
			if (path[i] == NULL)
			{
				printf("%s: not found\n", argv[0]);
			}
		}

	} while (length != -1);

	free(buffer);
	return (0);
}
int executePath(char *execPath, char **argv)
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
		execve(execPath, argv, NULL);
	}
	else
	{
		wait(&status);
	}
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
char **_getPath(void)
{
	char *pathtok;
	char *path;
	int i;
	char **splitpath;

	path = _getenv("PATH");
	splitpath = malloc(sizeof(char) * 1024);

	pathtok = strtok(path, ":");

	for (i = 0; pathtok != NULL; i++)
	{
		splitpath[i] = pathtok;
		pathtok = strtok(NULL, ":");

	}
	return (splitpath);
}
char *_getenv(const char *name)
{
	int i;
	size_t l = strlen(name);

	if (!__environ || !*name || strchr(name, '=')) return (NULL);
	for (i=0; __environ[i] && (strncmp(name, __environ[i], l)
		|| __environ[i][l] != '='); i++);
	if (__environ[i]) return __environ[i] + l+1;
	return (NULL);
}
