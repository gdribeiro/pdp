#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <mpi.h>

#define SIZE 100


int main(int argc, char *argv[]){

	int *v1, *v2, *res, rank, *vp1, *vp2, *rest;
	int groupSize;

	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &groupSize);


// Allocates memory
if (rank == 0) {
	if (!(v1 = (int *)malloc(SIZE * sizeof(int)))) {
		exit (0);
	}
	if (!(v2 = (int *)malloc(SIZE * sizeof(int)))) {
		exit (0);
	}
	if (!(rest = (int *)malloc(SIZE * sizeof(int)))) {
		exit (0);
	}
	if (!(vp1 = (int *)malloc(SIZE/groupSize*sizeof(int)))) {
		exit (0);
	}
	if (!(vp2 = (int *)malloc(SIZE/groupSize*sizeof(int)))) {
		exit (0);
	}
	if (!(res = (int *)malloc(SIZE/groupSize*sizeof(int)))) {
		exit (0);
	}
} else {
	if (!(res = (int *)malloc(SIZE/groupSize*sizeof(int)))) {
		exit (0);
	}
	if (!(vp1 = (int *)malloc(SIZE/groupSize*sizeof(int)))) {
		exit (0);
	}
	if (!(vp2 = (int *)malloc(SIZE/groupSize*sizeof(int)))) {
		exit (0);
	}
}
// Fill vectors with random numbers
if (rank == 0) {
	int i;
	for (i = 0; i < SIZE; i++) {
		v1[i] = 2;
		// v1[i] = (rand()%1) * INT_MAX;
	}
	memcpy(v2, v1, sizeof(int)*SIZE);

	for (i = 0; i < SIZE; i++) {
		fprintf(stderr, "%d ", v1[i]);
	}
	fprintf(stderr, "\n");
	for (i = 0; i < SIZE; i++) {
		fprintf(stderr, "%d ", v2[i]);
	}
	fprintf(stderr, "\n");
}



if (rank == 0) {
	int i;
	for (i = 0; i < groupSize; i++) {
		memcpy(vp1, &v1[i* groupSize], SIZE/groupSize*sizeof(int));
		memcpy(vp2, &v2[i* groupSize], SIZE/groupSize*sizeof(int));

		MPI_Send(vp1, SIZE/groupSize, MPI_INT, i,100, MPI_COMM_WORLD);
		MPI_Send(vp2, SIZE/groupSize, MPI_INT, i, 100, MPI_COMM_WORLD);
	}

	MPI_Recv(vp1, SIZE/groupSize, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
	MPI_Recv(vp2, SIZE/groupSize, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);


	for (i = 0; i < SIZE/groupSize; i++) {
		fprintf(stderr, "%d ", vp1[i]);
	}
	fprintf(stderr, "\n");
	for (i = 0; i < SIZE/groupSize; i++) {
		fprintf(stderr, "%d ", vp2[i]);
	}
	fprintf(stderr, "\n");

	for (i = 0; i < SIZE/groupSize; i++) {
		res[i] = vp1[i] * vp2[i];
		fprintf(stderr, "%d ", res[i]);
	}
	fprintf(stderr, "\n");


	MPI_Send(res, SIZE/groupSize, MPI_INT, 0, 100, MPI_COMM_WORLD);

	for (i = 0; i < groupSize; i++) {
		MPI_Recv(&rest[i* SIZE/groupSize], SIZE/groupSize, MPI_INT, i, 100, MPI_COMM_WORLD, &status);
	}

	} else {
		int i = 0;
		MPI_Recv(vp1, SIZE/groupSize, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
		MPI_Recv(vp2, SIZE/groupSize, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);

		for (i = 0; i < SIZE/groupSize; i++) {
			fprintf(stderr, "%d ", vp1[i]);
		}
		fprintf(stderr, "\n");
		for (i = 0; i < SIZE/groupSize; i++) {
			fprintf(stderr, "%d ", vp2[i]);
		}
		fprintf(stderr, "\n");

		for (i = 0; i < SIZE/groupSize; i++) {
			res[i] = vp1[i] * vp2[i];
			fprintf(stderr, "%d ", res[i]);
		}
		fprintf(stderr, "\n");

		MPI_Send(res, SIZE/groupSize, MPI_INT, 0, 100, MPI_COMM_WORLD);
	}


	// Allocates memory
	if (rank == 0) {
		int i=0;
		for (i = 0; i < SIZE; i++) {
			fprintf(stderr, "%d ", rest[i]);
		}
			fprintf(stderr, "\n");
		free(v1);
		free(v2);
		free(rest);
	} else {
		free(res);
		free(vp1);
		free(vp2);
	}

	MPI_Finalize();
	return 0;
}
