#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data[10];

    if (rank == 0) {
        for (int i = 0; i < 10; i++) {
            data[i] = i + 1;
        }
        printf("Rank 0: broadcasting data = [");
        for (int i = 0; i < 10; i++) printf(" %d", data[i]);
        printf(" ]\n");
    }

    MPI_Bcast(data, 10, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Rank %d: received data = [", rank);
    for (int i = 0; i < 10; i++) printf(" %d", data[i]);
    printf(" ]\n");

    MPI_Finalize();
    return 0;
}
