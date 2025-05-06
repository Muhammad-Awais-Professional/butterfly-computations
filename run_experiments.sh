#!/bin/bash

# Varying MPI processes
for mpi_processes in 2 4 8 16; do
    for omp_threads in 2 4 8; do
        export OMP_NUM_THREADS=$omp_threads
        echo "Running with $mpi_processes MPI processes and $omp_threads OpenMP threads"
        mpirun -np $mpi_processes ./butterfly_parallel_with_timing
    done
done

