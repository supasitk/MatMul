#include <stdio.h>
#include <stdlib.h>

void usage(void)
{
	printf("Usage:\n");
	printf("\t-s <size>\n");
	exit(-1);
}

int main(int argc, char *argv[])
{
	int size;

	while ((argc > 1) && (argv[1][0] == '-'))
	{
		switch (argv[1][1])
		{
			case 's':
				size = atoi(argv[2]);
				break;

			default:
				printf("Wrong argument: %s\n", argv[1]);
				usage();
		}
		argv += 2;
		argc -= 2;
	}	

	printf("Matrix size: %d\n", size);

	return 0;
}
