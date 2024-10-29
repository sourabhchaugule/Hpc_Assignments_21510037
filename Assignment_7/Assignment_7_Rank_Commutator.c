#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size, color, new_rank, new_size;
    MPI_Comm new_comm;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    color = rank % 5;

    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &new_comm);

    MPI_Comm_rank(new_comm, &new_rank);
    MPI_Comm_size(new_comm, &new_size);

    printf("Global rank: %d, Group: %d, New rank: %d, New group size: %d\n", rank, color, new_rank, new_size);

    MPI_Comm_free(&new_comm);
    MPI_Finalize();

    return 0;
}

