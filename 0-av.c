#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int ac, char **av)
{
	int i;

	for (i = 0; av[i] != NULL; i++)
		printf("avs: %s\n", av[i]);

	return (0);


}
