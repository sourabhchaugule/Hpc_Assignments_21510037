// Ring send message 



#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    int send_data, recv_data;

    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    send_data = rank; 
    printf("Process %d sending data %d\n", rank, send_data);

    int next = (rank + 1) % size; 
    int prev = (rank - 1 + size) % size; 

    MPI_Send(&send_data, 1, MPI_INT, next, 0, MPI_COMM_WORLD); // Blocking send
    MPI_Recv(&recv_data, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Blocking receive

    printf("Process %d received data %d from Process %d\n", rank, recv_data, prev);

    MPI_Finalize(); 
    return 0;
}

