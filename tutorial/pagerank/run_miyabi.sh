#!/bin/bash
#PBS -q debug-g
#PBS -l select=16:mpiprocs=4
#PBS -W group_list=gc64
#PBS -o latest_result.txt
#PBS -j oe

NUM_NODES=16
MPI_PROCS=4

cd ${PBS_O_WORKDIR}

mkdir -p result

TIMESTAMP=$(date +"%Y%m%d%H%M%S")
RESULT_FILE="result/pagerank_${NUM_NODES}nodes_${MPI_PROCS}ppn_${TIMESTAMP}.txt"

# Generate graph if not exists
# . venv/bin/activate/
# GRAPH_NODES=10000
# GRAPH_AVG_EDGE=500
# python3 preprocess/generate_graph.py --n_node=${GRAPH_NODES} --avg_degree=${GRAPH_AVG_EDGE}

# Compile pagerank_naive with MPI
cd naive
mpicc -o pagerank_naive main.c graph_loader.c -lm
echo "Compiling pagerank_naive with MPI..."

# Run pagerank_naive with MPI
cd ../
echo "Running pagerank_naive with MPI..."
for N in 10 100 1000 10000; do
    mpirun -np $((NUM_NODES * MPI_PROCS)) ./naive/pagerank_naive $N
done

# move result and attach symbolic link
mv latest_result.txt ${RESULT_FILE}

