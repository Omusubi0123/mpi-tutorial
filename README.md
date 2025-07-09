# MPI Tutorial
This was made for Speaking at the Taura Laboratory, The University of Tokyo, on 2025/07/09.

## Slide
`mpi-tutorial.pdf` is a slide for the MPI tutorial. It covers the following topics:
- MPI Overview
- Basic Learning of MPI
    - MPI Terminology
    - `MPI_Send` and `MPI_Recv`
- Collective Communication
    - `MPI_Bcast`
    - `MPI_Scatter` and `MPI_Gather`
    - `MPI_Allgather`
    - `MPI_Reduce` and `MPI_Allreduce`
- Application Example
    - run MPI program on Multi-node Cluster
    - PageRank Implementation

## Programs
Folder Structure:
```
├── tutorial
│   ├── allgather.c
│   ├── allreduce.c
│   ├── barrier.c
│   ├── bcast.c
│   ├── bin
│   ├── comm_split.c
│   ├── compare_bcast.c
│   ├── gather.c
│   ├── hello
│   │   ├── mpi_hello.c
│   │   ├── mpi_hello.cpp
│   │   └── mpi_send_recv.cpp
│   ├── Makefile
│   ├── pagerank
│   │   ├── create_venv.sh
│   │   ├── csr
│   │   │   ├── graph_loader.c
│   │   │   ├── graph_loader.h
│   │   │   ├── main.c
│   │   │   └── run.sh
│   │   ├── data
│   │   │   ├── 10
│   │   │   │   ├── graph.png
│   │   │   │   └── graph.txt
│   │   │   └── 100
│   │   │       ├── graph.png
│   │   │       └── graph.txt
│   │   ├── naive
│   │   │   ├── graph_loader.c
│   │   │   ├── graph_loader.h
│   │   │   ├── main.c
│   │   │   ├── pagerank_naive
│   │   │   └── run.sh
│   │   ├── preprocess
│   │   │   ├── generate_graph.py
│   │   │   └── visualize.py
│   │   └── run_miyabi.sh
│   ├── reduce.c
│   ├── scatter.c
│   ├── scatter2.c
│   ├── send_recv.c
│   └── send_recv2.c
```