import matplotlib.pyplot as plt

# Example data (replace with actual execution times)
mpi_processes = [2, 4, 8, 16]
execution_times = [10.0, 5.0, 3.0, 2.0]  # Replace with actual execution times

# Plot the results
plt.plot(mpi_processes, execution_times, label='Execution Time', marker='o')
plt.xlabel('Number of MPI Processes')
plt.ylabel('Execution Time (seconds)')
plt.title('Execution Time vs. Number of MPI Processes')
plt.grid(True)
plt.show()

