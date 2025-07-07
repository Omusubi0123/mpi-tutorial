#ifndef GRAPH_LOADER_H
#define GRAPH_LOADER_H

typedef struct {
    int n_rows;     // 自分が担当する行数
    int offset;     // 行番号の開始（global）
    int *row_ptr;
    int *col_idx;
    double *val;
    int n_total_nodes;  // グラフ全体のノード数（MPI全体共有）
} CSRMatrix;

int read_graph_csr_mpi(const char *filename, CSRMatrix *mat);

void free_csr(CSRMatrix *mat);

#endif
