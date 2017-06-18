#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	int   i, j, n;
	int a[100][100], b[100], c[100], sum;

	/* Some initializations */
	n = 100;
	for (i=0; i < n; i++)
	  b[i] = 1;
	sum = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			a[i][j] = 1; //rand()% 10;
		}
	}

	#pragma omp parallel for reduction(+:sum)
	  for (i=0; i < n; i++) {
			sum =0;
			for ( j = 0; i < n; i++) {
				sum += a[i][j] * b[j];
			}
			c[i] = sum;
		}


		for (i=0; i < n; i++)
			printf(" %i",sum);
		sum = 0;
 printf("\n");
}
