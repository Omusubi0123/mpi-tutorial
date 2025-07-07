import random

def generate_large_graph(n_nodes: int, avg_degree: int, filename: str):
    with open(filename, "w") as f:
        for src in range(n_nodes):
            targets = random.sample(range(n_nodes), avg_degree + random.randint(-avg_degree, avg_degree))
            for tgt in targets:
                f.write(f"{src} {tgt}\n")

if __name__ == "__main__":
    n_nodes = 100
    avg_degree = 5
    filename = "data/graph.txt"
    generate_large_graph(n_nodes=n_nodes, avg_degree=avg_degree, filename=filename)
