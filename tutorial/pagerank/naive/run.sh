mpicc -o pagerank_naive main.c graph_loader.c -lm
mpirun -np 4 ./pagerank_naive
