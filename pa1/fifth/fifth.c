#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "fifth.h"

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
	multiplyPrint(file);
	fclose(file);
	return 0;
}

/* Takes a pointer to a file and created three matrices,
 * * one to hold the first matrix, another to hold the 
 *  * second matrix, and a third one to hold the product
 *   * of the matrices. If the matrices are not possible
 *    * to multiply, the function prints error and terminates.
 *     * If possible, multiplies the two matrices and stores
 *      * them in a result.
 *       */
void multiplyPrint(FILE *file){
	int r, c;
        int m1, n1, number1;
        int m2, n2, number2;
        int **first_matrix, **second_matrix, **result;
        int *arr1, *arr2, *arr3;
        fscanf(file, "%d %d\n", &m1, &n1);
        first_matrix = (int **) malloc(m1 * sizeof(int *));
        
	for(r = 0; r < m1; r++){
                arr1 = (int *) malloc(n1 * sizeof(int));
                for(c = 0; c < n1; c++){
                        fscanf(file, "%d", &number1);
                        arr1[c] = number1;
                }
                first_matrix[r] = arr1;
        }
	
        fscanf(file, "%d %d\n", &m2, &n2);
        
	/* Checks to see if the matrices are able to be multiplied */
	if(n1 != m2){
                printf("error\n");
                exit(0);
        }
	
        second_matrix = (int **) malloc(m2 * sizeof(int *));
        for(r = 0; r < m2; r++){
                arr2 = (int *) malloc(m2 * sizeof(int *));
                for(c = 0; c < n2; c++){
                        fscanf(file, "%d", &number2);
                        arr2[c] = number2;
                }
                second_matrix[r] = arr2;
        }

        result = (int**) malloc(m1 * sizeof(int *));
        for(r = 0; r < m1; r++){
                arr3 = (int *) malloc(n2 * sizeof(int));
                result[r] = arr3;
        }

        int temp = 0;
        int i;
        for(r = 0; r < m1; r++){
                for(c = 0; c < n2; c++){
                        for(i = 0; i < m2; i++){
                                temp = temp + first_matrix[r][i] * second_matrix[i][c];
                        }
                        result[r][c] = temp;
                        temp = 0;
                }
        }
	
	for(r = 0; r < m1; r++){
                for(c = 0; c < n2; c++){
                        printf("%d\t", result[r][c]);
                }
                printf("\n");
        }
	return;
}
