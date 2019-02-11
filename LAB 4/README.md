# Lab 4: Divide and Conquer parallelism with OpenMP: Sorting

## Deliverable

### Analysis with Tareador
1. Include the relevant parts of the modified **multisort-tareador.c** code and comment where the calls to the Tareador API have been placed. Comment also about the task graph generated and the causes of the dependences that appear.

2. Write a table with the execution time and speed-up predicted by Tareador (for 1, 2, 4, 8, 16, 32 and 64 processors) for the task decomposition specified with Tareador. Are the results close to the ideal case? Reason about your answer.

### Parallelization and performance analysis with tasks
1. Include the relevant portion of the codes that implement the two versions (_Leaf_ and _Tree_), commenting whatever necessary.

2. For the the _Leaf_ and _Tree_ strategies, include the speed{up (strong scalability) plots that have been obtained for the different numbers of processors. Reason about the performance that is observed, including captures of Paraver windows to justify your explanations.

### Parallelization and performance analysis with dependent tasks
1. Include the relevant portion of the code that implements the Tree version with task dependencies, commenting whatever necessary.
2. Reason about the performance that is observed, including the speed-up plots that have been obtained different numbers of processors and with captures of Paraver windows to justify your reasoning.

### Optional
1. If you have done any of the optional parts in this laboratory assignment, please include and comment in your report the relevant portions of the code and performance plots that have been obtained.