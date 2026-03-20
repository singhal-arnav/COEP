#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024 //Matrix size

int** create_matrix() {
    int **matrix = (int**)malloc(SIZE * sizeof(int *));
    for(int i = 0; i < SIZE; i++)
        matrix[i] = (int*)malloc(SIZE * sizeof(int));
    return matrix;
}

void init_matrix(int **matrix) {
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            matrix[i][j] = rand() % 100;
}

void add_matrices(int **A, int **B, int **C) {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void free_matrix(int **matrix) {
    for(int i = 0; i < SIZE; i++)
        free(matrix[i]);
    free(matrix);
}

int main() {
    int **A = create_matrix();
    int **B = create_matrix();
    int **C = create_matrix();

    init_matrix(A);
    init_matrix(B);

    add_matrices(A, B, C);

    printf("Matrix addition completed.\n");

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);

    return 0;
}