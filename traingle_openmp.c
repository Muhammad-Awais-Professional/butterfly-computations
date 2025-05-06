#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int **adj_matrix = NULL;
int num_nodes = 0;

// Function to allocate memory for adjacency matrix
int **allocate_matrix(int n) {
    int **matrix = malloc(n * sizeof(int *));
    if (!matrix) {
        perror("malloc failed for matrix rows");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        matrix[i] = calloc(n, sizeof(int));
        if (!matrix[i]) {
            perror("calloc failed for matrix cols");
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

// Function to free matrix memory
void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Load graph from file
void load_graph(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    int max_node = 0;
    int u, v;

    // First pass: find max node id
    while (fscanf(file, "%d %d", &u, &v) == 2) {
        if (u > max_node) max_node = u;
        if (v > max_node) max_node = v;
    }

    num_nodes = max_node + 1;

    // Allocate adjacency matrix
    adj_matrix = allocate_matrix(num_nodes);

    rewind(file); // Reset file pointer

    // Second pass: build matrix
    while (fscanf(file, "%d %d", &u, &v) == 2) {
        adj_matrix[u][v] = 1;
        adj_matrix[v][u] = 1; // undirected graph
    }

    fclose(file);
}

// Count triangles using OpenMP
int count_triangles() {
    int triangle_count = 0;

    #pragma omp parallel for reduction(+:triangle_count)
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

    return triangle_count;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s graph.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    load_graph(argv[1]);

    double start_time = omp_get_wtime();
    int total_triangles = count_triangles();
    double end_time = omp_get_wtime();

    printf("Total triangles: %d\n", total_triangles);
    printf("Execution time: %f seconds\n", end_time - start_time);

    free_matrix(adj_matrix, num_nodes);
    return 0;
}

