// Matrix Matrix Multiplication 


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

void matrix_multiply(int N, double *A, double *B, double *C, int local_N) {
    for (int i = 0; i < local_N; i++) {
        for (int j = 0; j < N; j++) {
            C[i * N + j] = 0; 
            for (int k = 0; k < N; k++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size, N = 4; 
    double *A, *B, *C, *local_A, *local_C;
    int local_N;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        A = (double *)malloc(N * N * sizeof(double));
        B = (double *)malloc(N * N * sizeof(double));
        C = (double *)malloc(N * N * sizeof(double));
        
    }

    local_N = N / size; 
    local_A = (double *)malloc(local_N * N * sizeof(double));
    B = (double *)malloc(N * N * sizeof(double)); 
    local_C = (double *)malloc(local_N * N * sizeof(double));

    MPI_Scatter(A, local_N * N, MPI_DOUBLE, local_A, local_N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    start_time = MPI_Wtime();
    matrix_multiply(N, local_A, B, local_C, local_N);
    end_time = MPI_Wtime();

    MPI_Gather(local_C, local_N * N, MPI_DOUBLE, C, local_N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Resulting Matrix C:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%lf ", C[i * N + j]);
            }
            printf("\n");
        }
        printf("Time taken: %lf seconds\n", end_time - start_time);

        free(A);
        free(B);
        free(C);
    }

    free(local_A);
    free(local_C);

    MPI_Finalize();
    return 0;
}

