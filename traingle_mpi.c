#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 5000000

typedef struct {
    int u, v;
} Edge;

Edge edges[MAX_EDGES];

int compare(const void* a, const void* b) {
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    if (ea->u != eb->u) return ea->u - eb->u;
    return ea->v - eb->v;
}

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 2) {
        if (rank == 0) printf("Usage: %s <input_file>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        if (rank == 0) perror("File open failed");
        MPI_Finalize();
        return 1;
    }

    int edge_count = 0;
    while (fscanf(file, "%d %d", &edges[edge_count].u, &edges[edge_count].v) == 2) {
        if (edges[edge_count].u != edges[edge_count].v) {
            if (edges[edge_count].u > edges[edge_count].v) {
                int tmp = edges[edge_count].u;
                edges[edge_count].u = edges[edge_count].v;
                edges[edge_count].v = tmp;
            }
            edge_count++;
        }
    }
    fclose(file);

    qsort(edges, edge_count, sizeof(Edge), compare);

    int chunk = edge_count / size;
    int start = rank * chunk;
    int end = (rank == size - 1) ? edge_count : start + chunk;

    int local_triangles = 0;
    for (int i = start; i < end; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;

        for (int j = 0; j < edge_count; ++j) {
            if (edges[j].u == v) {
                int w = edges[j].v;
                for (int k = 0; k < edge_count; ++k) {
                    if (edges[k].u == u && edges[k].v == w) {
                        local_triangles++;
                    }
                }
            }
        }
    }

    int total_triangles = 0;
    MPI_Reduce(&local_triangles, &total_triangles, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total triangles: %d\n", total_triangles / 3); // each triangle is counted 3 times
    }

    MPI_Finalize();
    return 0;
}

