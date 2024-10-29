// Write a mpi program to give a example of deadlock 

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    int MESSAGE_SIZE = 100000;
    int buffer[MESSAGE_SIZE];
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0) {
        MPI_Send(buffer, MESSAGE_SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(buffer, MESSAGE_SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else if (rank == 1) {
        MPI_Send(buffer, MESSAGE_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(buffer, MESSAGE_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    MPI_Finalize();
    return 0;
}   
