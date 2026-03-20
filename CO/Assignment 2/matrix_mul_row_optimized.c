#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024 //Matrix size

int** create_matrix() {
    int **matrix = (int**)malloc(SIZE * sizeof(int *));
    for(int i = 0; i < SIZE; i++)
        matrix[i] = (int*)calloc(SIZE, sizeof(int));
    return matrix;
}

void init_matrix(int **matrix) {
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            matrix[i][j] = rand() % 100;
}

void multiply_matrices(int **A, int **B, int **C, int tile_size) {
    for(int i = 0; i < SIZE; i += tile_size) {
        for(int j = 0; j < SIZE; j += tile_size) {
            for(int k = 0; k < SIZE; k += tile_size) {
                for(int ii = i; ii < i + tile_size && ii < SIZE; ii++) {
                    for(int jj = j; jj < j + tile_size && jj < SIZE; jj++) {
                        for(int kk = k; kk < k + tile_size && kk < SIZE; kk++) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }    
}

void free_matrix(int **matrix) {
    for(int i = 0; i < SIZE; i++)
        free(matrix[i]);
    free(matrix);
}

int main(int argc, char **argv) {
    int **A = create_matrix();
    int **B = create_matrix();
    int **C = create_matrix();

    init_matrix(A);
    init_matrix(B);

    multiply_matrices(A, B, C, atoi(argv[1]));

    printf("Matrix multiplication completed.\n");

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);

    return 0;
}
