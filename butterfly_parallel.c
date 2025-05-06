#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

#define N 1024  // Size of the problem (adjust as needed)

void butterfly_computation(int rank, int size) {
    // Butterfly computation (dummy operation for illustration)
    #pragma omp parallel for
    for (int i = rank; i < N; i += size) {
        // Perform some computation for each task
        // Replace with the actual butterfly operation
        printf("Process %d, Thread %d: Computing index %d\n", rank, omp_get_thread_num(), i);
    }
}

int main(int argc, char** argv) {
    int rank, size;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Start OpenMP parallel region
    #pragma omp parallel
    {
        butterfly_computation(rank, size);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}

