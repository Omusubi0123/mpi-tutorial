#ifndef GRAPH_LOADER_H
#define GRAPH_LOADER_H

typedef struct {
    int n_nodes;
    int n_edges;
    int *out_degree;
    double **M;
} Graph;

int read_graph(const char *filename, Graph *g);
void free_graph(Graph *g);

#endif
