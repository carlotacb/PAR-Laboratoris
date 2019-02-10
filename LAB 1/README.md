# Lab 1: Experimental setup and tools

## Deliverable

### Node architecture and memory:

1. Complete the following table with the relevant architectural characteristics of the different node types available in _boada_:

|                                    | boada-1 to boada-4 | boada-5 | boada-6 to boada-8 |
|------------------------------------|--------------------|---------|--------------------|
| Number of sockets per node         |                    |         |                    |
| Number of cores per socket         |                    |         |                    |
| Number of threads per core         |                    |         |                    |
| Maximum core frequency             |                    |         |                    |
|------------------------------------|--------------------|---------|--------------------|
| L1-I cache size (per-core)         |                    |         |                    |
| L1-D cache size (per-core)         |                    |         |                    |
| L2 cache size (per-core)           |                    |         |                    |
| Last-level cache size (per-socket) |                    |         |                    |
|------------------------------------|--------------------|---------|--------------------|
| Main memory size (per socket)      |                    |         |                    |
| Main memory size (per node)        |                    |         |                    |

2. Include in the document the arhitectural diagram for one of the nodes _boada-1_ to _boada-4_ as obtained when using the _lstopo_ command.

### Timing sequential and parallel executions:

3. Plot the execution time and speed{up that is obtained when varying the number of threads (strong scalability) and problem size (weak scalability) for **pi_omp.c** on the different node types available in _boada_. Reason about the results that are obtained.

### Analysis of task decompositions with _Tareador_

4. Include the relevant(s) part(s) of the code to show the new task definition(s) in v4 of **3dfft_seq.c**. Capture the final task dependence graph that has been obtained after version v4.

5. Complete the following table for the initial and different versions generated for **3dfft_seq.c**, briefly commenting the evolution of the metrics with the different versions.

| Version | T1 | Tinf | Parallelism |
|---------|----|------|-------------|
|   seq   |    |      |             |
|    v1   |    |      |             |
|    v2   |    |      |             |
|    v3   |    |      |             |
|    v4   |    |      |             |

6. With the results from the parallel simulation with 2, 4, 8, 16 and 32 processors, draw the execution time and speedup plots for version v4 with respect to the sequential  execution (that you can estimate from the simulation of the initial task decomposition that we provided in **3dfft_seq.c**, using just 1 processor). Briefly comment the scalability  behaviour shown on these two plots.

### Tracing the execution of parallel programs

7. From the analysis with _Paraver_ that you have done for the complete parallelization of **3dfft_omp.c**, explain how have you computed the value for \phi, the parallel fraction of the application. Please, include any Paraver timeline that may help to understand how you have performed the computation of \phi.

8. Show and comment the profile of the % of time spent in the different OpenMP states for the complete parallelization of **3dfft_omp.c** on 4 threads.