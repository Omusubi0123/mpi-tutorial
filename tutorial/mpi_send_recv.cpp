#include <mpi.h>
#include <iostream>
#include <cstdlib>

/* 後で定義する関数の前方宣言 */
void send_data();
void recv_data();

/*
 * 2つのプロセスの間で配列データを送る
 *
 * 実行方法: mpiexec -n 2 mpi_sample2
 */
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int num_procs;
    int my_rank;

    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (num_procs != 2) {
        std::cerr << "Run this program in MPI with 2 processes." << std::endl;
        return EXIT_FAILURE;
    }

    // send data from rank 0 to rank 1
    if (my_rank == 0) {
        send_data();
    } else {
        recv_data();
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}

void send_data()
{
    double send_data[10];
    for (int i = 0; i < 10; i++) {
        send_data[i] = (double) i;
    }
    const double *data_address = &send_data[0];
    int data_count = 10;
    std::cout << "Sending data." << std::endl;
    std::cout << "send_data: [";
    for (int i = 0; i < 10; i++)
    {
        std::cout << " " << send_data[i];
    }
    std::cout << " ]" << std::endl;
    MPI_Send(
        data_address, /* データ(バッファ)の先頭アドレス。MPIはここから読み出すだけなのでconst */
        data_count, /* 要素数 */
        MPI_DOUBLE, /* 送るデータの型。バッファの型に合わせる。間違えると受信データがおかしくなる。 */
        1, /* 送り先のrank */
        0, /* タグと呼ぶ数値。同時期に同じ送信先に違う意味合いのデータを送る時に区別するための番号。自分で値を決める */
        MPI_COMM_WORLD /* ノードを用途別にグループ分けした時にグループを識別するための値 */
    );
}

void recv_data()
{
    double data[10];
    double *data_address = &data[0];
    int data_count = 10;
    MPI_Status st; /* 通信の成否コードを受け取るための変数 */

    std::cout << "Receiving data." << std::endl;
    MPI_Recv(
        data_address, /* データ(バッファ)の先頭アドレス。MPIはここに書き込むので非const */
        data_count, /* 受信するデータの個数。 */
        MPI_DOUBLE, /* 受信するデータの型。 */
        0, /* 送り元のrank */
        0, /* タグ */
        MPI_COMM_WORLD,
        &st
    );
    std::cout << "recv_data: [";
    for (int i = 0; i < 10; i++)
    {
        std::cout << " " << data[i];
    }
    std::cout << " ]" << std::endl;
}
