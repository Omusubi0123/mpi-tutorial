#include "graph_loader.h"
#include <stdio.h>
#include <stdlib.h>

int read_graph(const char *filename, Graph *g) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return -1;
    }

    if (fscanf(fp, "%d", &g->n_nodes) != 1) {
        fprintf(stderr, "Failed to read node count\n");
        return -1;
    }

    g->out_degree = calloc(g->n_nodes, sizeof(int));
    g->M = malloc(g->n_nodes * sizeof(double *));
    for (int i = 0; i < g->n_nodes; i++) {
        g->M[i] = calloc(g->n_nodes, sizeof(double));
    }

    int from, to;
    g->n_edges = 0;
    while (fscanf(fp, "%d %d", &from, &to) == 2) {
        g->M[to][from] += 1.0;
        g->out_degree[from]++;
        g->n_edges++;
    }
    fclose(fp);

    // 正規化：M[to][from] /= out_degree[from]
    for (int i = 0; i < g->n_nodes; i++) {
        for (int j = 0; j < g->n_nodes; j++) {
            if (g->out_degree[j] > 0) {
                g->M[i][j] /= g->out_degree[j];
            }
        }
    }

    return 0;
}

void free_graph(Graph *g) {
    for (int i = 0; i < g->n_nodes; i++) {
        free(g->M[i]);
    }
    free(g->M);
    free(g->out_degree);
}
