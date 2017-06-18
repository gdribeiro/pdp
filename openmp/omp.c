#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000

int main(int argc, char *argv[]){
	int i, j, k;
	double initial;
	time_t t;

	srand((unsigned) time(&t));

	initial = omp_get_wtime();

	int **matrixA = (int **)malloc(SIZE * sizeof(int*)), **matrixB = (int **)malloc(SIZE * sizeof(int*)), **matrixC = (int **)malloc(SIZE * sizeof(int*));

	for(int i = 0; i < SIZE; i++){
		matrixA[i] = (int *)malloc(SIZE * sizeof(int));
		matrixB[i] = (int *)malloc(SIZE * sizeof(int));
		matrixC[i] = (int *)malloc(SIZE * sizeof(int));
	}


	for (i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++){
			matrixA[i][j] = (i == j ? 1 : 0); //rand() % 1000;
			matrixB[i][j] = (i == j ? 1 : 0) ;//rand() % 1000;
			matrixC[i][j] = 0;
		}
	}

		#pragma omp parallel private(i) num_threads(16)
	{
		//printf("for 1: %d \n", omp_get_thread_num());
		for(i = 0; i < SIZE; i++) {
				{
					# pragma omp for private(j, k)
					for(j = 0; j < SIZE; j++){
					{
						//printf("for 2: %d \n", omp_get_thread_num());
						#pragma	taskloop
							for(k = 0; k < SIZE; k++){
								//printf("for 3: %d \n", omp_get_thread_num());
								matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
							}
						}
				}
		}
		}
}

		//
		// for (i = 0; i < SIZE; i++){
		// 	for(j = 0; j < SIZE; j++){
		// 		printf(" %d ", matrixC[i][j]);
		// 	}
		// 	printf("\n");
		// }

		printf("Time: %f \n",  omp_get_wtime() - initial);


	return 0;
}
