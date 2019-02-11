# Lab 2: OpenMP programming model and analysis of overheads

## Deliverable

### Part I: OpenMP questionnaire

When answering to the questions in this questionnaire, please DO NOT simply answer with yes, no or a number; try to minimally justify all your answers. Sometimes you may need to execute several times in order to see the effect of data races in the parallel execution.

A) Basics

1. **hello.c**

	1. How many times will you see the "Hello world!" message if the program is executed with "./1.hello"?
	2. Without changing the program, how to make it to print 4 times the "Hello World!" message?

2. **hello.c**: Assuming the _OMP_NUM_THREADS_ variable is set to 8 with "_export OMP_NUM_THREADS=8_"
	1. Is the execution of the program correct? (i.e., prints a sequence of "(Thid) Hello (Thid) world!" being Thid the thread identifier) Which data sharing clause should be added to make it correct?
	2. Are the lines always printed in the same order? Could the messages appear intermixed?

3. **how many.c**: Assuming the _OMP_NUM_THREADS_ variable is set to 8 with "export _OMP_NUM_THREADS=8_"
	1. How many "Hello world ..." lines are printed on the screen?
	2. If the if(0) clause is commented in the last parallel directive, how many "Hello world ..." lines are printed on the screen?

4. **data sharing.c**
	1. Which is the value of variable x after the execution of each parallel region with different data-sharing attribute (shared, private and firstprivate)?
	2. What needs to be changed/added/removed in the first directive to ensure that the value after the first parallel is always 8?

5. **parallel.c**
	1. How many messages the program prints? Which iterations is each thread executing?
	2. Change the for loop to ensure that its iterations are distributed among all participating threads.

6. **datarace.c** (execute several times before answering the questions)
	1. Is the program always executing correctly?
	2. Add two alternative directives to make it correct. Explain why they make the execution correct.

7. **barrier.c**
	1. Can you predict the sequence of messages in this program? Do threads exit from the barrier in any specific order?

B) Worksharing

1. **for.c**
	1. How many and which iterations from the loop are executed by each thread? Which kind of schedule is applied by default?
	2. Which directive should be added so that the first printf is executed only once by the first thread that finds it?

2. **schedule.c**
	1. Which iterations of the loops are executed by each thread for each schedule kind?

3. **nowait.c**
	1. How does the sequence of printf change if the nowait clause is removed from the first for directive?
	2. If the nowait clause is removed in the second for directive, will you observe any difference?

4. **collapse.c**
	1. Which iterations of the loop are executed by each thread when the collapse clause is used?
	2. Is the execution correct if the collapse clause is removed? Which clause (different than collapse) should be added to make it correct?

5. **ordered.c**
	1. Can you explain the order in which printf appear?
	2. How can you ensure that a thread always executes two consecutive iterations in order during the execution of the ordered part of the loop body?

6. **doacross.c**
	1. In which order are the "Outside" and "Inside" messages printed?
	2. In which order are the iterations in the second loop nest executed?
	3. What would happen if you remove the invocation of sleep(1). Execute several times to answer in the general case.

C) Tasks

1. **serial.c**
	1. Is the code printing what you expect? Is it executing in parallel?

2. **parallel.c**
	1. Is the code printing what you expect? What is wrong with it?
	2. Which directive should be added to make its execution correct?
	3. What would happen if the firstprivate clause is removed from the task directive? And if the firstprivate clause is ALSO removed from the parallel directive? Why are they redundant?
	4. Why the program breaks when variable p is not firstprivate to the task?
	5. Why the firstprivate clause was not needed in 1.serial.c?

3. **taskloop.c**
	1. Execute the program several times and make sure you are able to explain when each thread in the threads team is actually contributing to the execution of work (tasks)  generated in the taskloop.

### Part II: Parallelization overheads

1. Which is the order of magnitude for the overhead associated with a parallel region (fork and join) in _OpenMP_? Is it constant? Reason the answer based on the results reported by the **pi_omp_parallel.c** code.
2. Which is the order of magnitude for the overhead associated with the creation of a task and its synchronization at taskwait in _OpenMP_? Is it constant? Reason the answer based on the results reported by the **pi_omp_tasks.c** code.
3. Based on the results reported by the **pi_omp_taskloop.c** code, If you have to generate tasks out of a loop, what seems to be better: to use _task_ or _taskloop_? Try to reason the answer. 
4. Which is the order of magnitude for the overhead associated with the execution of critical regions in _OpenMP_? How is this overhead decomposed? How and why does the overhead associated with critical increase with the number of processors? Identify at least three reasons that justify the observed performance degradation. Base your answers on the execution times reported by the **pi_omp.c** and **pi_omp_critical.c** programs and their _Paraver_ execution traces.
5. Which is the order of magnitude for the overhead associated with the execution of atomic memory accesses in _OpenMP_? How and why does the overhead associated with atomic increase with the number of processors? Reason the answers based on the execution times reported by the **pi_omp.c** and **pi_omp_atomic.c** programs.
6. In the presence of false sharing (as it happens in pi omp sumvector.c), which is the additional average time for each individual access to memory that you observe? What is causing this increase in the memory access time? Reason the answers based on the execution times reported by the **pi_omp_sumvector.c** and **pi_omp_padding.c** programs. Explain how padding is done in **pi_omp_padding.c**.
