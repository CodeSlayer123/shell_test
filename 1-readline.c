#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *buffer;
	size_t bufsize;
	ssize_t length;

	buffer = malloc(bufsize * sizeof(char));

	do
	{
		printf("$ ");
		length = getline(&buffer, &bufsize, stdin);
		printf("%s", buffer);

		if (strcmp(buffer, "exit\n") == 0)
		{
			break;
		}

} while (length != -1);


	free(buffer);
	return (0);
}
