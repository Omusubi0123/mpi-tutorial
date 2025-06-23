#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int data_count = 10;
    int numbers[data_count];
    if (world_rank == 0) {
        for (int i = 0; i < 10; i++) {
            numbers[i] = i + 1;
        }
        printf("Send Data:");
        for (int i = 0; i < 10; i++) {
            printf(" %d", numbers[i]);
        }
        printf("\n");
        MPI_Send((void *)&numbers, data_count, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (world_rank == 1) {
        MPI_Recv(&numbers, data_count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received Data:");
        for (int i = 0; i < 10; i++) {
            printf(" %d", numbers[i]);
        }
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}