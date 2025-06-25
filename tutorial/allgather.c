#include <mpi.h>
#include <stdio.h>

#define ITEMS_PER_PROC 2

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_data[ITEMS_PER_PROC];
    send_data[0] = rank * 10;
    send_data[1] = rank * 10 + 1;

    int recv_data[ITEMS_PER_PROC * size];

    MPI_Allgather(send_data, ITEMS_PER_PROC, MPI_INT,
                  recv_data, ITEMS_PER_PROC, MPI_INT,
                  MPI_COMM_WORLD);

    printf("Rank %d received:", rank);
    for (int i = 0; i < ITEMS_PER_PROC * size; i++)
        printf(" %d", recv_data[i]);
    printf("\n");

    MPI_Finalize();
    return 0;
}
