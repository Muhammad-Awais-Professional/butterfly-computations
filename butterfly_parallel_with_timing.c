#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>  // If you're using OpenMP

int main(int argc, char *argv[]) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Record start time
    double start_time = MPI_Wtime();

    // Perform the butterfly computation (example - replace this with your algorithm)
    // Start parallel computation with MPI and OpenMP
    #pragma omp parallel for // Use OpenMP parallelism here if needed
    for (int i = 0; i < 10000; i++) {
        // Computation for butterfly (replace with actual logic)
    }

    // Record end time
    double end_time = MPI_Wtime();
    printf("Process %d execution time: %f seconds\n", rank, end_time - start_time);

    // Finalize MPI
    MPI_Finalize();

    return 0;
}

