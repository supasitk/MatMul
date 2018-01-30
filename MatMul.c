#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#ifdef OMP
#include <omp.h>
#endif

typedef int TYPE;
#define HIGH 	10
#define LOW 	1

void usage(void)
{
	printf("Usage:\n");
	printf("\t-s <size of matrix>\n");
	printf("\t-t <number of thread>\n");
	exit(-1);
}

int main(int argc, char *argv[])
{
	int i, j, k, sum;
	time_t seed;
	float elapsed_time;
	struct timeval t1, t2;
	int size, num_threads;
	TYPE **A, **B, **C;

	/* Extract parameters of command */
	while ((argc > 1) && (argv[1][0] == '-'))
	{
		switch (argv[1][1])
		{
			case 's':
				size = atoi(argv[2]);
				break;
			case 't':
				num_threads = atoi(argv[2]);
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
	gettimeofday(&t1, NULL);
	
	A = malloc(size * sizeof(TYPE *));
	B = malloc(size * sizeof(TYPE *));
	C = malloc(size * sizeof(TYPE *));
	for (i=0; i<size; i++)
	{
		A[i] = malloc(size * sizeof(TYPE));
		B[i] = malloc(size * sizeof(TYPE));
		C[i] = malloc(size * sizeof(TYPE));
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

	gettimeofday(&t2, NULL);
	elapsed_time = (float)((t2.tv_sec * 1000000 + t2.tv_usec) - (t1.tv_sec * 1000000 + t1.tv_usec)) / 1000000; 
	printf("Execution Time = %f seconds.\n", elapsed_time);
	printf("----------------------------------------------------------------\n");


	/* Matrix multiplication */
	printf("Matrix Multiplication is being processed with %d threads........\n", num_threads);
	gettimeofday(&t1, NULL);

#ifdef OMP
	omp_set_num_threads(num_threads);
#endif

	sum = 0;
#ifdef OMP
	#pragma omp parallel for private(i, j, k, sum)
#endif
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

	gettimeofday(&t2, NULL);
	elapsed_time = (float)((t2.tv_sec * 1000000 + t2.tv_usec) - (t1.tv_sec * 1000000 + t1.tv_usec)) / 1000000; 
	printf("Execution Time = %f seconds.\n", elapsed_time);
	printf("----------------------------------------------------------------\n");
	
	printf("Completed!!!\n");

	return 0;
}
