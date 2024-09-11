#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n = 1000;
    int i, j, k, num_threads;
    double start_time, end_time, serial_time, parallel_time, speedup;

    double **A = (double **)malloc(n * sizeof(double *));
    double **B = (double **)malloc(n * sizeof(double *));
    double **C = (double **)malloc(n * sizeof(double *));
    
    for (i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        B[i] = (double *)malloc(n * sizeof(double));
        C[i] = (double *)malloc(n * sizeof(double));
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
            C[i][j] = 0.0;
        }
    }

    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    start_time = omp_get_wtime();
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    end_time = omp_get_wtime();
    serial_time = end_time - start_time;

    start_time = omp_get_wtime();
    #pragma omp parallel for private(i, j, k) num_threads(num_threads)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;

    speedup = serial_time / parallel_time;
    printf("Matrix-Matrix Multiplication Speedup: %f\n", speedup);

    for (i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}

