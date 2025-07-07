mpicc -o pagerank_csr main.c graph_loader.c -lm
mpirun -np 4 ./pagerank_csr
