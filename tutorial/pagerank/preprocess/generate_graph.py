# tutorial/pagerank/で実行すること
import os
import random
import argparse

def generate_large_graph(n_nodes: int, avg_degree: int, filename: str):
    if not os.path.exists(os.path.dirname(filename)):
        os.mkdir(os.path.dirname(filename))
    with open(filename, "w") as f:
        f.write(f"{n_nodes}\n")
        for src in range(n_nodes):
            targets = random.sample(range(n_nodes), avg_degree + random.randint(-avg_degree, avg_degree))
            for tgt in targets:
                f.write(f"{src} {tgt}\n")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate a random graph for PageRank.")
    parser.add_argument("--n_nodes", type=int, default=10, help="Number of nodes in the graph")
    parser.add_argument("--avg_degree", type=int, default=4, help="Average degree of each node")
    parser.add_argument("--filename", type=str, default=None, help="Output filename")

    args = parser.parse_args()
    n_nodes = args.n_nodes
    avg_degree = args.avg_degree
    filename = args.filename or f"data/{n_nodes}/graph.txt"
    
    generate_large_graph(n_nodes=n_nodes, avg_degree=avg_degree, filename=filename)
