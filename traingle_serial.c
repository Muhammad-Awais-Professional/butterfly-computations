#include <stdio.h>
#include <stdlib.h>

int **allocate_matrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)calloc(n, sizeof(int));
    }
    return matrix;
}

void load_graph(const char *filename, int ***adj_matrix, int *num_nodes) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File open failed");
        exit(1);
    }

    int u, v, max_node = 0;
    int edges[200000][2], edge_count = 0;

    while (fscanf(fp, "%d %d", &u, &v) == 2) {
        edges[edge_count][0] = u;
        edges[edge_count][1] = v;
        edge_count++;
        if (u > max_node) max_node = u;
        if (v > max_node) max_node = v;
    }
    fclose(fp);

    *num_nodes = max_node + 1;
    *adj_matrix = allocate_matrix(*num_nodes);

    for (int i = 0; i < edge_count; i++) {
        u = edges[i][0];
        v = edges[i][1];
        (*adj_matrix)[u][v] = 1;
        (*adj_matrix)[v][u] = 1;
    }
}

int main() {
    int **adj_matrix;
    int num_nodes;

    load_graph("facebook_combined.txt", &adj_matrix, &num_nodes);

    int triangle_count = 0;

    for (int i = 0; i < num_nodes; i++) {
        for (int j = i + 1; j < num_nodes; j++) {
            if (adj_matrix[i][j]) {
                for (int k = j + 1; k < num_nodes; k++) {
                    if (adj_matrix[i][k] && adj_matrix[j][k]) {
                        triangle_count++;
                    }
                }
            }
        }
    }

    printf("Total triangles found (Serial): %d\n", triangle_count);

    for (int i = 0; i < num_nodes; i++) free(adj_matrix[i]);
    free(adj_matrix);
    return 0;
}

