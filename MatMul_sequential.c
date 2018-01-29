#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HIGH 	10
#define LOW 	1

void usage(void)
{
	printf("Usage:\n");
	printf("\t-s <size>\n");
	exit(-1);
}

int main(int argc, char *argv[])
{
	int i, j, k, sum;
	time_t seed, start, end;
	double cpu_time_used;
	int size;
	int **A, **B, **C;

	/* Extract parameters of command */
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

	/* Allocate memory and initialize value of matrix */ 	
	printf("Initializing Matrix [%dx%d]........\n", size, size);
	start = clock();
	
	A = malloc(size * sizeof(int *));
	B = malloc(size * sizeof(int *));
	C = malloc(size * sizeof(int *));
	for (i=0; i<size; i++)
	{
		A[i] = malloc(size * sizeof(int));
		B[i] = malloc(size * sizeof(int));
		C[i] = malloc(size * sizeof(int));
	} 

	time(&seed);
	srand((unsigned int) seed);
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			A[i][j] = rand() % (HIGH - LOW + 1) + LOW;
			B[i][j] = rand() % (HIGH - LOW + 1) + LOW;
		}
	}

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Execution Time = %f seconds.\n", cpu_time_used);
	printf("----------------------------------------------------------------\n");


	/* Matrix multiplication */
	printf("Matrix Multiplication is being processed........\n");
	start = clock();
	
	sum = 0;
	for (i=0; i<size; i++)
	{
		for (j=0; j<size; j++)
		{
			for (k=0; k<size; k++)
			{
				sum = sum + (A[i][k] * B[k][j]); 
			}
		}
		C[i][j] = sum;
		sum = 0;
	}

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Execution Time = %f seconds.\n", cpu_time_used);
	printf("----------------------------------------------------------------\n");
	
	printf("Completed!!!\n");

	return 0;
}
