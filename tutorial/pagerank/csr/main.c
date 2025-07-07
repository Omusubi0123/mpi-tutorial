#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph_loader.h"

#define DAMPING 0.85
#define TOL 1e-6
#define MAX_ITER 100

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    CSRMatrix mat;
    read_graph_csr_mpi("graph.txt", &mat);

    int N = mat.n_total_nodes;
    double *x = malloc(N * sizeof(double));
    double *x_new_local = malloc(mat.n_rows * sizeof(double));

    for (int i = 0; i < N; i++) x[i] = 1.0 / N;

    for (int iter = 0; iter < MAX_ITER; iter++) {
        for (int i = 0; i < mat.n_rows; i++) {
            double sum = 0.0;
            for (int j = mat.row_ptr[i]; j < mat.row_ptr[i + 1]; j++) {
                sum += mat.val[j] * x[mat.col_idx[j]];
            }
            x_new_local[i] = DAMPING * sum + (1.0 - DAMPING) / N;
        }

        MPI_Allgatherv(x_new_local, mat.n_rows, MPI_DOUBLE,
                       x, NULL, NULL, MPI_DOUBLE, MPI_COMM_WORLD);

        if (rank == 0) {
            double diff = 0.0;
            for (int i = 0; i < N; i++) diff += fabs(x[i] - x_new_local[i % mat.n_rows]);
            printf("[Iter %d] diff = %e\n", iter + 1, diff);
            if (diff < TOL) break;
        }
    }

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            printf("Node %d: %.6f\n", i, x[i]);
        }
    }

    free(x);
    free(x_new_local);
    free_csr(&mat);
    MPI_Finalize();
    return 0;
}
