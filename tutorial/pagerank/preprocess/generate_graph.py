# tutorial/pagerank/で実行すること
import os
import random

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
    n_nodes = 10
    avg_degree = 4
    filename = f"data/{n_nodes}/graph.txt"
    generate_large_graph(n_nodes=n_nodes, avg_degree=avg_degree, filename=filename)
