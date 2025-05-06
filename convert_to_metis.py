from collections import defaultdict

# Load edge list
adj = defaultdict(set)
with open("facebook_combined.txt", "r") as f:
    for line in f:
        u, v = map(int, line.strip().split())
        if u != v:
            adj[u + 1].add(v + 1)  # Convert 0-based to 1-based
            adj[v + 1].add(u + 1)

# Write in METIS format
num_nodes = max(adj.keys())
with open("facebook_metis.graph", "w") as out:
    out.write(f"{num_nodes} {sum(len(neigh) for neigh in adj.values()) // 2}\n")
    for i in range(1, num_nodes + 1):
        out.write(" ".join(map(str, sorted(adj[i]))) + "\n")

