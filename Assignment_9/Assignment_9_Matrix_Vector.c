// Matrix_vector Multiplication 


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int rank, size;
    int rows = 4, cols = 4; 
    double *A = NULL; 
    double *X = NULL; 
    double *Y = NULL; 
    double *local_A = NULL; 
    double *local_Y = NULL; 
    int local_rows; 
    double start_time, end_time; 

    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) {
            printf("This program requires at least 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        A = (double*)malloc(rows * cols * sizeof(double));
        X = (double*)malloc(cols * sizeof(double));
        Y = (double*)malloc(rows * sizeof(double));

        // Initialize the matrix and vector
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                A[i * cols + j] = i + j;  
            }
        }
        for (int i = 0; i < cols; i++) {
            X[i] = i + 1;  
        }
    }

    
    MPI_Bcast(&rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&cols, 1, MPI_INT, 0, MPI_COMM_WORLD);

   
    local_rows = rows / size; // Assume rows is divisible by size for simplicity
    local_A = (double*)malloc(local_rows * cols * sizeof(double));
    local_Y = (double*)malloc(local_rows * sizeof(double));

    // Distribute the rows of A to all processes
    MPI_Scatter(A, local_rows * cols, MPI_DOUBLE, local_A, local_rows * cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Broadcast the vector X to all processes
    X = (double*)malloc(cols * sizeof(double));
    if (rank == 0) {
        // X initialized in process 0
        for (int i = 0; i < cols; i++) {
            X[i] = i + 1;  // Example initialization
        }
    }
    MPI_Bcast(X, cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Start timing the computation
    start_time = MPI_Wtime();

    // Perform local computation: local_Y = local_A * X
    for (int i = 0; i < local_rows; i++) {
        local_Y[i] = 0.0;
        for (int j = 0; j < cols; j++) {
            local_Y[i] += local_A[i * cols + j] * X[j];
        }
    }

    // End timing the computation
    end_time = MPI_Wtime();

    // Gather the results from all processes to Y in process 0
    if (rank == 0) {
        Y = (double*)malloc(rows * sizeof(double));
    }
    MPI_Gather(local_Y, local_rows, MPI_DOUBLE, Y, local_rows, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Process 0 prints the final result and computation time
    if (rank == 0) {
        printf("Result vector Y:\n");
        for (int i = 0; i < rows; i++) {
            printf("%f ", Y[i]);
        }
        printf("\n");
    }

    // Print the computation time for each process
    double total_time = end_time - start_time;
    printf("Process %d computed in %f seconds\n", rank, total_time);

    // Free allocated memory
    free(local_A);
    free(local_Y);
    if (rank == 0) {
        free(A);
        free(X);
        free(Y);
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}

