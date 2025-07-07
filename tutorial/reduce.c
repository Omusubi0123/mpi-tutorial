#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int value = rank + 1;
    int sum;

    MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    double average = (double)sum / size;
    if (rank == 0) {
        printf("Rank %d: sum = %d, avg = %.2f\n", rank, sum, average);
    } else {
        printf("Rank %d: sum = %d, avg = %.2f\n", rank, sum, average);
    }

    MPI_Finalize();
    return 0;
}
