#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // ランクが偶数なら color=0, 奇数なら color=1 に分ける
    int color = rank % 3;

    MPI_Comm new_comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &new_comm);

    int new_rank, new_size;
    MPI_Comm_rank(new_comm, &new_rank);
    MPI_Comm_size(new_comm, &new_size);

    printf("World Rank %d => Group %d, New Rank %d of %d\n",
           rank, color, new_rank, new_size);

    MPI_Comm_free(&new_comm);  // 新しいコミュニケータの解放
    MPI_Finalize();
    return 0;
}
