# triangle_count_serial.py
import networkx as nx
import time

start = time.time()
G = nx.read_edgelist("facebook_combined.txt", nodetype=int)
triangle_count = sum(nx.triangles(G).values()) // 3
end = time.time()

print(f"Total triangles: {triangle_count}")
print(f"Time taken: {end - start:.2f} seconds")

