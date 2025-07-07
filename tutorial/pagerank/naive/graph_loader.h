#ifndef GRAPH_LOADER_H
#define GRAPH_LOADER_H

#define MAX_NODES 100000
#define MAX_EDGES 1000000

extern int edge_from[MAX_EDGES];
extern int edge_to[MAX_EDGES];
extern int out_degree[MAX_NODES];
extern double M[MAX_NODES][MAX_NODES];  // 疎行列化する場合は別構造に変更

int read_graph(const char *filename, int *n_nodes);

#endif
