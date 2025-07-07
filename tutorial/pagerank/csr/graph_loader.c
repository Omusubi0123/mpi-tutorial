#include "graph_loader.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 10000000

typedef struct {
    int from, to;
} Edge;

int read_graph_csr_mpi(const char *filename, CSRMatrix *mat) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    Edge *edges = NULL;
    int n_edges = 0;
    int n_nodes = 0;

    if (rank == 0) {
        FILE *fp = fopen(filename, "r");
        if (!fp) {
            perror("fopen");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        edges = malloc(sizeof(Edge) * MAX_EDGES);
        while (fscanf(fp, "%d %d", &edges[n_edges].from, &edges[n_edges].to) == 2) {
            if (edges[n_edges].from > n_nodes) n_nodes = edges[n_edges].from;
            if (edges[n_edges].to > n_nodes) n_nodes = edges[n_edges].to;
            n_edges++;
        }
        fclose(fp);
        n_nodes++;  // 0-indexed
    }

    MPI_Bcast(&n_nodes, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n_edges, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) edges = malloc(sizeof(Edge) * n_edges);
    MPI_Bcast(edges, n_edges * sizeof(Edge), MPI_BYTE, 0, MPI_COMM_WORLD);

    int rows_per_rank = n_nodes / size;
    int remainder = n_nodes % size;
    int my_rows = rows_per_rank + (rank < remainder ? 1 : 0);
    int offset = rank * rows_per_rank + (rank < remainder ? rank : remainder);

    int *row_ptr = calloc(my_rows + 1, sizeof(int));
    int *tmp_counts = calloc(n_nodes, sizeof(int));

    for (int i = 0; i < n_edges; i++) {
        if (edges[i].from >= offset && edges[i].from < offset + my_rows) {
            tmp_counts[edges[i].from - offset]++;
        }
    }

    for (int i = 0; i < my_rows; i++) {
        row_ptr[i + 1] = row_ptr[i] + tmp_counts[i];
    }

    int nnz = row_ptr[my_rows];
    int *col_idx = malloc(nnz * sizeof(int));
    double *val = malloc(nnz * sizeof(double));
    int *cur = calloc(my_rows, sizeof(int));
    int *out_deg = calloc(n_nodes, sizeof(int));

    for (int i = 0; i < n_edges; i++) {
        out_deg[edges[i].from]++;
    }

    for (int i = 0; i < n_edges; i++) {
        int from = edges[i].from;
        int to = edges[i].to;

        if (from >= offset && from < offset + my_rows) {
            int row = from - offset;
            int dest = row_ptr[row] + cur[row];
            col_idx[dest] = to;
            val[dest] = 1.0 / out_deg[from];
            cur[row]++;
        }
    }

    free(edges);
    free(tmp_counts);
    free(cur);
    free(out_deg);

    mat->n_rows = my_rows;
    mat->offset = offset;
    mat->row_ptr = row_ptr;
    mat->col_idx = col_idx;
    mat->val = val;
    mat->n_total_nodes = n_nodes;

    return 0;
}

void free_csr(CSRMatrix *mat) {
    free(mat->row_ptr);
    free(mat->col_idx);
    free(mat->val);
}
