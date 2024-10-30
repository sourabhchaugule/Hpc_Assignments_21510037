// Size Redu 


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int message_sizes[] = {1, 10 , 100, 500, 1000 }; // Different message sizes
    int num_sizes = sizeof(message_sizes) / sizeof(message_sizes[0]);

    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (int j = 0; j < num_sizes; j++)
    {
        int size = message_sizes[j];
        char *input_buffer = malloc(size * sizeof(char));
        char *output_buffer = malloc(size * sizeof(char));

        srand(time(NULL) + rank); // Seed randomness with a unique value for each rank

        for (int i = 0; i < size; i++)
            input_buffer[i] = rand() % 256;

        double total_time = 0.0;
        double start_time = 0.0;

        for (int i = 0; i < 100; i++)
        {
            MPI_Barrier(MPI_COMM_WORLD);
            start_time = MPI_Wtime();

            MPI_Reduce(input_buffer, output_buffer, size, MPI_BYTE, MPI_BOR, 0, MPI_COMM_WORLD);
            MPI_Barrier(MPI_COMM_WORLD);
            total_time += (MPI_Wtime() - start_time);
        }

        if (rank == 0)
        {
            printf("Message Size: %d bytes, Average Time for Reduce: %f secs\n", size, total_time / 100);
        }

        free(input_buffer);
        free(output_buffer);
    }

    MPI_Finalize();
    return 0;
}

