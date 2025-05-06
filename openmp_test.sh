#!/bin/bash

# Run with different OMP_NUM_THREADS values
for threads in 2 4 8 16 32
do
    echo "Running with $threads threads"
    export OMP_NUM_THREADS=$threads
    ./triangle_openmp facebook_combined.txt
done

