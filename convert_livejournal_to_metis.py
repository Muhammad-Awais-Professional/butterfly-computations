import networkx as nx

def convert_to_metis(input_file, output_file):
    # Read the graph from the edge list, skip lines starting with '%'
    G = nx.read_edgelist(input_file, nodetype=int, comments='%')

    with open(output_file, 'w') as f:
        # METIS format requires: number of nodes and number of edges
        f.write(f"{G.number_of_nodes()} {G.number_of_edges()}\n")
        
        # Create adjacency list
        for node in range(1, G.number_of_nodes() + 1):
            neighbors = sorted([n for n in G.neighbors(node)]) if node in G else []
            f.write(" ".join(str(neighbor) for neighbor in neighbors) + "\n")

    print(f"Graph successfully converted to METIS format and saved in {output_file}")

# Full correct path to input file
input_file = '/home/dell/Desktop/butterfly_pdc/soc-LiveJournal1/out.soc-LiveJournal1'
output_file = 'livejournal_metis.graph'

convert_to_metis(input_file, output_file)

