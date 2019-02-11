# Lab 3: Embarrassingly parallelism with OpenMP: Mandelbrot set

## Deliverable

### Task granularity analysis

1. Which are the two most important common characteristics of the task graphs generated for the two task granularities (_Row_ and _Point_) for the non-graphical version of _mandel-tareador_? Obtain the task graphs that are generated in both cases for -w 8.

2. Which section of the code is causing the serialization of all tasks in mandeld-tareador? How do you plan to protect this section of code in the parallel OpenMP code?

### OpenMP task-based parallelization

1. For the _Row_ and _Point_ decompositions of the non-graphical version, include the execution time and speed-up plots obtained in the strong scalability analysis (with -i 10000). Reason about the causes of good or bad performance in each case.

### OpenMP taskloop{based parallelization

1. For the _Row_ and _Point_ decompositions of the non-graphical version, include the execution time and speed-up plots obtained in the strong scalability analysis (with -i 10000). Reason about the causes of good or bad performance in each case.

### OpenMP for{based parallelization

1. For the the _Row_ and _Point_ decompositions of the non-graphical version, include the execution time and speed-up plots that have been obtained for the 4 different loop schedules when using 8 threads (with -i 10000). Reason about the performance that is observed.

2. For the _Row_ parallelization strategy, complete the following table with the information extracted from the Extrae instrumented executions (with 8 threads and -i 10000) and analysis with Paraver, reasoning about the results that are obtained.

|                                                                  | static | static,10 | dynamic,10 | guided,10 |
|------------------------------------------------------------------|--------|-----------|------------|-----------|
|                  Running average time per thread                 |        |           |            |           |
|    Execution unbalance (average time divided by maximum time)    |        |           |            |           |
| SchedForkJoin (average time per thread or time if only one does) |        |           |            |           |