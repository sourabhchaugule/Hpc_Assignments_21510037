// Plotting 1 


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define MESSAGE_SIZE 1024 // Fixed message size (1KB)

int main(int argc, char **argv) {
    int my_rank, p;
    char *message = NULL;
    double start_time, end_time;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    // Allocate memory for the message only on the root process
    if (my_rank == 0) {
        message = (char *)malloc(MESSAGE_SIZE * sizeof(char));
        // Initialize message (optional)
        for (int i = 0; i < MESSAGE_SIZE; i++) {
            message[i] = 'a';
        }
    } else {
        message = (char *)malloc(MESSAGE_SIZE * sizeof(char));
    }

    // Synchronize all processes before starting the broadcast
    MPI_Barrier(MPI_COMM_WORLD);
    
    // Start timing the broadcast
    start_time = MPI_Wtime();
    
    // Perform the broadcast
    MPI_Bcast(message, MESSAGE_SIZE, MPI_CHAR, 0, MPI_COMM_WORLD);
    
    // End timing the broadcast
    end_time = MPI_Wtime();
    
    // Print the time taken for the broadcast on the root process
    if (my_rank == 0) {
        printf("Time taken for broadcast with %d processes: %f seconds\n", p, end_time - start_time);
    }

    // Free the allocated memory
    free(message);

    // Finalize MPI
    MPI_Finalize();
    return 0;
}

