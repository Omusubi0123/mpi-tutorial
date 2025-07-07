#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include "graph_loader.h"

#define DAMPING 0.85
#define TOL 1e-6
#define MAX_ITER 100

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    Graph g;
    if (read_graph("../data/10/graph.txt", &g) != 0) {
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int n = g.n_nodes;

    // データ分割（行分割）
    int rows_per_proc = n / size;
    int remainder = n % size;
    int my_rows = rows_per_proc + (rank < remainder ? 1 : 0);
    int my_start = rank * rows_per_proc + (rank < remainder ? rank : remainder);

    // PageRankベクトルxと各プロセスが担当する新しいベクトルnew_x_local(len(my_rows)次元)を確保
    double *x = malloc(n * sizeof(double));
    double *new_x_local = malloc(my_rows * sizeof(double));
    
    // 全プロセスで保持するの新しいPageRankベクトルnew_x_full(n次元)を確保
    double *new_x_full = malloc(n * sizeof(double));
    int *recvcounts = malloc(size * sizeof(int));
    int *displs = malloc(size * sizeof(int));

    for (int i = 0; i < n; i++) x[i] = 1.0 / n;

    for (int i = 0; i < size; i++) {
        recvcounts[i] = rows_per_proc + (i < remainder ? 1 : 0);
        displs[i] = i * rows_per_proc + (i < remainder ? i : remainder);
    }

    for (int iter = 0; iter < MAX_ITER; iter++) {
        for (int i = 0; i < my_rows; i++) {
            int global_i = my_start + i;
            new_x_local[i] = 0.0;
            for (int j = 0; j < n; j++) {
                new_x_local[i] += g.M[global_i][j] * x[j];
            }
            new_x_local[i] = DAMPING * new_x_local[i] + (1.0 - DAMPING) / n;
        }

        MPI_Allgatherv(new_x_local, my_rows, MPI_DOUBLE,
                       new_x_full, recvcounts, displs, MPI_DOUBLE, MPI_COMM_WORLD);

        // チェック用：rank 0 が diff を計算
        double diff = 0.0;
        if (rank == 0) {
            for (int i = 0; i < n; i++) {
                diff += fabs(new_x_full[i] - x[i]);
            }
            printf("[Iter %d] diff = %f\n", iter + 1, diff);
        }

        // 全rankにdiffをブロードキャスト（終了判定共有）
        MPI_Bcast(&diff, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        if (diff < TOL) break;

        // x を更新
        for (int i = 0; i < n; i++) x[i] = new_x_full[i];
    }

    free(new_x_full);
    free(recvcounts);
    free(displs);
    
    // 結果表示
    if (rank == 0) {
        printf("\nFinal PageRank:\n");
        for (int i = 0; i < n; i++) {
            printf("Node %d: %.6f\n", i, x[i]);
        }
    }

    free(x);
    free(new_x_local);
    free_graph(&g);
    
    MPI_Finalize();
    return 0;
}
