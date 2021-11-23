#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **splitter(char fun[])
{
	char **holder;
	char *tmp;
	long int length = strlen(fun);
	int i = 0;

	holder = malloc(sizeof(char) * (length * 2));

	tmp = strtok(fun, " ");
	holder[i] = tmp;
	while (tmp != NULL)
	{
		i++;
		tmp = strtok(NULL, " ");
		holder[i] = tmp;
	}
	return (holder);
}
