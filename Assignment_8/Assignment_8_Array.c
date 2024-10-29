// n/2 to both process addition 


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char **argv) {
    int rank, size;
    int n = 8; 
    int A[n];
    int local_sum = 0, total_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processes

    if (size != 2) {
        if (rank == 0) {
            printf("This program requires exactly 2 processes.\n");
        }
        MPI_Finalize();
        return;
    }

    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            A[i] = i + 1; 
        }
    }

    MPI_Bcast(A, n, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        for (int i = 0; i < n / 2; i++) {
            local_sum += A[i]; 
        }
    } else if (rank == 1) {
        for (int i = n / 2; i < n; i++) {
            local_sum += A[i]; 
        }
    }

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        printf("Total Sum: %d\n", total_sum);
    }

    MPI_Finalize();
}

