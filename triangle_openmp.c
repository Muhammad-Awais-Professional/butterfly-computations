#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_NODES 100000

int adj[MAX_NODES][MAX_NODES] = {0}; // Adjacency matrix
int num_nodes = 0;

void load_graph(const char *filename) {
    FILE *file = fopen(filename, "r");
    int u, v;
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    while (fscanf(file, "%d %d", &u, &v) == 2) {
        if (u >= MAX_NODES || v >= MAX_NODES) continue;
        adj[u][v] = 1;
        adj[v][u] = 1;
        if (u > num_nodes) num_nodes = u;
        if (v > num_nodes) num_nodes = v;
    }

    num_nodes++; // To include the last node
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <edge_list_file>\n", argv[0]);
        return 1;
    }

    load_graph(argv[1]);

    double start_time = omp_get_wtime();
    long long triangle_count = 0;

    #pragma omp parallel for reduction(+:triangle_count) schedule(dynamic)
    for (int i = 0; i < num_nodes; i++) {
        for (int j = i + 1; j < num_nodes; j++) {
            if (adj[i][j]) {
                for (int k = j + 1; k < num_nodes; k++) {
                    if (adj[i][k] && adj[j][k]) {
                        triangle_count++;
                    }
                }
            }
        }
    }

    double end_time = omp_get_wtime();

    printf("Total triangles: %lld\n", triangle_count);
    printf("Time taken: %.2f seconds\n", end_time - start_time);

    return 0;
}

