#include <mpi.h>
#include <stdio.h>
#include <unistd.h>  // for sleep

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);  // MPIの初期化

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // 各プロセスのランク取得
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // 全体のプロセス数取得

    printf("Rank %d: before barrier\n", rank);
    
    // 任意でランクごとに少し遅らせる（バリアの動作確認用）
    sleep(rank);

    // ここで全プロセスの同期をとる
    MPI_Barrier(MPI_COMM_WORLD);

    printf("Rank %d: after barrier\n", rank);

    MPI_Finalize();  // MPIの終了
    return 0;
}
