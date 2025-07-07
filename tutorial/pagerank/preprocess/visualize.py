# tutorial/pagerank/で実行すること
import networkx as nx
import matplotlib.pyplot as plt
import random

def visualize_graph(load_file: str, save_file: str, sample_nodes: int = -1):
    G = nx.DiGraph()
    with open(load_file, "r") as f:
        n = int(f.readline().strip())
        for line in f:
            u, v = map(int, line.strip().split())
            G.add_edge(u, v)

    if sample_nodes != -1:
        sampled_nodes = random.sample(list(G.nodes), sample_nodes)
    else:
        sampled_nodes = list(G.nodes)
    H = G.subgraph(sampled_nodes)

    plt.figure(figsize=(10, 10))
    nx.draw_networkx(H, node_size=30, arrowsize=10, with_labels=True)
    # pos = nx.spring_layout(H, k=0.5, seed=42)  # レイアウトを調整してばらけさせる
    # nx.draw_networkx(H, pos=pos, node_size=30, arrowsize=10, with_labels=True)
    plt.title("Sampled Graph View")
    plt.savefig(save_file, dpi=300)


if __name__ == "__main__":
    n_node = 10
    load_file = f"data/{n_node}/graph.txt"
    save_file = f"data/{n_node}/graph.png"
    visualize_graph(load_file=load_file, save_file=save_file)
