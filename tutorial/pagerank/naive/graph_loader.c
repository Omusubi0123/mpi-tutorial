#include <stdio.h>
#include "graph_loader.h"

int edge_from[MAX_EDGES], edge_to[MAX_EDGES];
int out_degree[MAX_NODES];
double M[MAX_NODES][MAX_NODES];

int read_graph(const char *filename, int *n_nodes) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return -1;
    }

    int max_node = 0, from, to, edge_count = 0;
    while (fscanf(fp, "%d %d", &from, &to) == 2) {
        edge_from[edge_count] = from;
        edge_to[edge_count] = to;
        out_degree[from]++;
        if (from > max_node) max_node = from;
        if (to > max_node) max_node = to;
        edge_count++;
    }
    fclose(fp);

    *n_nodes = max_node + 1;

    for (int i = 0; i < edge_count; i++) {
        int from = edge_from[i];
        int to = edge_to[i];
        M[to][from] = 1.0 / out_degree[from];
    }

    return 0;
}
