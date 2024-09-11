#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrixMultiplyDynamic(int **A, int **B, int **C, int N, int num_threads) {
    omp_set_num_threads(num_threads);
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrixMultiplySequential(int **A, int **B, int **C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int N = 500; 
    int num_threads;
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    int **A = (int **)malloc(N * sizeof(int *));
    int **B = (int **)malloc(N * sizeof(int *));
    int **C = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

    double start_time, end_time, sequential_time, parallel_time;


    start_time = omp_get_wtime();
    matrixMultiplySequential(A, B, C, N);
    end_time = omp_get_wtime();
    sequential_time = end_time - start_time;
    printf("Sequential Execution Time: %f seconds\n", sequential_time);


    start_time = omp_get_wtime();
    matrixMultiplyDynamic(A, B, C, N, num_threads);
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("Parallel Execution Time (with %d threads): %f seconds\n", num_threads, parallel_time);

    double speedup = sequential_time / parallel_time;
    printf("Speedup: %f\n", speedup);

    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}

