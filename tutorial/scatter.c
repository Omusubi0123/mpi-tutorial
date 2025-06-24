#include <mpi.h>
#include <stdio.h>

#define TOTAL_DATA 20

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // プロセス数で割り切れるように調整
    if (TOTAL_DATA % size != 0) {
        if (rank == 0)
            printf("Error: TOTAL_DATA (%d) must be divisible by number of processes (%d)\n", TOTAL_DATA, size);
        MPI_Finalize();
        return 1;
    }

    int send_data[TOTAL_DATA];
    int recv_count = TOTAL_DATA / size;
    int recv_data[recv_count];

    if (rank == 0) {
        for (int i = 0; i < TOTAL_DATA; i++) {
            send_data[i] = i;
        }
        printf("Rank 0: Scattering data...\n");
    }

    MPI_Scatter(send_data, recv_count, MPI_INT,
                recv_data, recv_count, MPI_INT,
                0, MPI_COMM_WORLD);

    printf("Rank %d received:", rank);
    for (int i = 0; i < recv_count; i++) {
        printf(" %d", recv_data[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}
