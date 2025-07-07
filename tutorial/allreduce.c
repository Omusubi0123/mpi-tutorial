#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int value = rank + 1;
    int total_sum = 0;

    MPI_Allreduce(&value, &total_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    double average = (double)total_sum / size;
    printf("Rank %d: total sum = %d, average = %.2f\n", rank, total_sum, average);

    MPI_Finalize();
    return 0;
}
