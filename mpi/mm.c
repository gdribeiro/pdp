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
			matrixA[i][j] = rand() % 1000;
			matrixB[i][j] = rand() % 1000;
			matrixC[i][j] = 0;
		}
	}

	for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++){
			for(k = 0; k < SIZE; k++){
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}
	
	printf("Time: %f \n",  omp_get_wtime() - initial);

	return 0;
}