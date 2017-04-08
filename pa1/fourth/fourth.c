#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "fourth.h"

int main(int argc, char **argv){
	if(access(argv[1], F_OK) == -1){
		printf("error\n");
		exit(0);
	}
	FILE *file = fopen(argv[1], "r");
	fseek(file, 0, SEEK_END);
	if(ftell(file) == 0){
		exit(0);
	}
	rewind(file);
	sumPrint(file);
	fclose(file);
	return 0;
}

/* Takes a pointer to a file and creates two matrices,
 * * one to hold the first matrix of the file and another
 *  * to hold the sum of both matrices in the file. Sums
 *   * the two matrices and stores them in the result.
 *    */
void sumPrint(FILE *file){
	int m, n, r, c, number;
        int **arr;
        int *arr2;
	fscanf(file, "%d %d\n", &m, &n);
        arr = (int **) malloc(m * sizeof(int*));
        for(r = 0; r < m; r++){
                arr2 = (int *) malloc(n * sizeof(int));
                for(c = 0; c < n; c++){
                        fscanf(file, "%d", &number);
                        arr2[c] = number;
                }
                arr[r] = arr2;
        }

	/* Sums up both arrays */
        for(r = 0; r < m; r++){
                arr2 = (int *) malloc(n * sizeof(int));
                for(c = 0; c < n; c++){
                        fscanf(file, "%d", &number);
                        arr[r][c] = arr[r][c] + number;
                }
        }

	for(r = 0; r < m; r++){
                for(c = 0; c < n; c++){
                        printf("%d\t", arr[r][c]);
                }
                printf("\n");
        }
	return;
}
