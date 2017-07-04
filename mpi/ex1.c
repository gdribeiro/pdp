#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <mpi.h>

#define SIZE 25000000


int main(int argc, char *argv[]){

	int *v1, *v2, *res, rank, *vp1, *vp2, *rest;
	int groupSize;

	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &groupSize);


// Allocates memory
if (rank == 0) {
	v1 = (int *)malloc(SIZE * sizeof(int));
	v2 = (int *)malloc(SIZE * sizeof(int));
	rest = (int *)malloc(SIZE * sizeof(int));

} else {
	res = (int *)malloc(SIZE/groupSize*sizeof(int));
	vp1 = (int *)malloc(SIZE/groupSize*sizeof(int));
	vp2 = (int *)malloc(SIZE/groupSize*sizeof(int));
}
// Fill vectors with random numbers
if (rank == 0) {
	int i;
	for (i = 0; i < SIZE; i++) {
		v1[i] = (rand()%1) * INT_MAX;
	}
	memcpy(v2, v1, sizeof(v1));
}



if (rank == 0) {
	int i;
	for (i = 0; i < groupSize; i++) {
		memcpy(vp1, &v1[i* groupSize], SIZE/groupSize);
		memcpy(vp2, &v2[i* groupSize], SIZE/groupSize);

		MPI_Send(vp1, SIZE/groupSize, MPI_INT,i,100,MPI_COMM_WORLD);
		MPI_Send(vp2, SIZE/groupSize, MPI_INT,i,100,MPI_COMM_WORLD);
	}

		MPI_Recv(rest, SIZE/groupSize, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);

	} else {
		MPI_Recv(vp1, SIZE/groupSize, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
		MPI_Recv(vp2, SIZE/groupSize, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);

		int i;
		for (i = 0; i < SIZE/groupSize; i++) {
			res[i] = vp1[1] * vp2[i];
		}

		MPI_Send(res, SIZE/groupSize, MPI_INT,0,100,MPI_COMM_WORLD);
	}



return 0;
}
