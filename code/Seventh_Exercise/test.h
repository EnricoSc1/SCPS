#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>


void multiply_matrices(double **A, double **B, double **C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double cij = 0.0;
            for (int l = 0; l < N; l++) {
                cij += A[i][l] * B[l][j];
            }
            C[i][j] = cij;
        }
    }
}

double **allocate_matrix(int N, double value) {
    double **matrix = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        matrix[i] = (double *)malloc(N * sizeof(double));
        for (int j = 0; j < N; j++) {
            matrix[i][j] = value;
        }
    }
    return matrix;
}

void free_matrix(double **matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

