import networkx as nx
import matplotlib.pyplot as plt

# Load the graph
def load_graph(graph_file):
    with open(graph_file, 'r') as f:
        lines = f.readlines()

    header = lines[0].strip().split()
    num_nodes = int(header[0])
    G = nx.Graph()

    for idx, line in enumerate(lines[1:num_nodes+1]):
        node = idx + 1
        neighbors = list(map(int, line.strip().split()))
        for neighbor in neighbors:
            G.add_edge(node, neighbor)

    return G

# Load partition info
def load_partition(part_file):
    with open(part_file, 'r') as f:
        partitions = [int(line.strip()) for line in f]
    return partitions

# Draw graph with colors by partition
def draw_partitioned_graph(G, partitions):
    color_map = []
    for node in G.nodes():
        color_map.append(partitions[node - 1])

    pos = nx.spring_layout(G, seed=42)
    nx.draw_networkx_nodes(G, pos, node_color=color_map, cmap=plt.cm.Set1, node_size=20)
    nx.draw_networkx_edges(G, pos, alpha=0.1)
    plt.title("METIS Graph Partitioning Visualization")
    plt.axis('off')
    plt.show()

# Main
graph_file = 'facebook_metis.graph'
part_file = 'facebook_metis.graph.part.4'

G = load_graph(graph_file)
partitions = load_partition(part_file)
draw_partitioned_graph(G, partitions)

