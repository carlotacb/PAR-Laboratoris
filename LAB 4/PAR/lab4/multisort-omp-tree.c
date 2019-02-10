#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include <sys/time.h>
double getusec_() {
        struct timeval time;
        gettimeofday(&time, NULL);
        return ((double)time.tv_sec * (double)1e6 + (double)time.tv_usec);
}

#define START_COUNT_TIME stamp = getusec_();
#define STOP_COUNT_TIME(_m) stamp = getusec_() - stamp;\
                        stamp = stamp/1e6;\
                        printf ("%s: %0.6f\n",(_m), stamp);

// N and MIN must be powers of 2
long N;
long MIN_SORT_SIZE;
long MIN_MERGE_SIZE;

#define BLOCK_SIZE 1024L

#define T int

void basicsort(long n, T data[n]);

void basicmerge(long n, T left[n], T right[n], T result[n*2], long start, long length);

void merge(long n, T left[n], T right[n], T result[n*2], long start, long length) {
        if (length < MIN_MERGE_SIZE*2L) {
                // Base case
                basicmerge(n, left, right, result, start, length);
        } else {
                // Recursive decomposition
		#pragma omp task
                merge(n, left, right, result, start, length/2);
               	#pragma omp task
		merge(n, left, right, result, start + length/2, length/2);
        }
}

void multisort(long n, T data[n], T tmp[n]) {
        if (n >= MIN_SORT_SIZE*4L) {
                // Recursive decomposition
		#pragma omp taskgroup 
		{
			#pragma omp task
                	multisort(n/4L, &data[0], &tmp[0]);
                	#pragma omp task
			multisort(n/4L, &data[n/4L], &tmp[n/4L]);
               		#pragma omp task
			multisort(n/4L, &data[n/2L], &tmp[n/2L]);
               		#pragma omp task
			multisort(n/4L, &data[3L*n/4L], &tmp[3L*n/4L]);
		}
		#pragma omp taskgroup 
		{
			#pragma omp task
        	        merge(n/4L, &data[0], &data[n/4L], &tmp[0], 0, n/2L);
       	        	#pragma omp task
			merge(n/4L, &data[n/2L], &data[3L*n/4L], &tmp[n/2L], 0, n/2L);
		}
		#pragma omp task
                merge(n/2L, &tmp[0], &tmp[n/2L], &data[0], 0, n);
	} else {
		// Base case
		basicsort(n, data);
	}
}

static void initialize(long length, T data[length]) {
   long i;
   for (i = 0; i < length; i++) {
      if (i==0) {
         data[i] = rand();
      } else {
         data[i] = ((data[i-1]+1) * i * 104723L) % N;
      }
   }
}

static void clear(long length, T data[length]) {
   long i;
   for (i = 0; i < length; i++) {
      data[i] = 0;
   }
}

void check_sorted(long n, T data[n]) 
{
   int unsorted=0;
   for (int i=1; i<n; i++)
      if (data[i-1] > data[i]) unsorted++;
   if (unsorted > 0)
      printf ("\nERROR: data is NOT properly sorted. There are %d unordered positions\n\n",unsorted);
   else {
//      printf ("data IS ordered; ");
   }
}

int main(int argc, char **argv) {

        if (argc != 4) {
                fprintf(stderr, "Usage: %s <vector size in K> <sort size in K> <merge size in K>\n", argv[0]);
                return 1;
        }

	N = atol(argv[1]) * BLOCK_SIZE;
	MIN_SORT_SIZE = atol(argv[2]) * BLOCK_SIZE;
        MIN_MERGE_SIZE = atol(argv[3]) * BLOCK_SIZE;

	T *data = malloc(N*sizeof(T));
	T *tmp = malloc(N*sizeof(T));
	
        double stamp;
        START_COUNT_TIME;

	initialize(N, data);
	clear(N, tmp);

        STOP_COUNT_TIME("Initialization time in seconds");

   	START_COUNT_TIME;
	
	#pragma omp parallel
	#pragma omp single
   	multisort(N, data, tmp);

   	STOP_COUNT_TIME("Multisort execution time");

   	START_COUNT_TIME;

   	check_sorted (N, data);

   	STOP_COUNT_TIME("Check sorted data execution time");

    	fprintf(stdout, "Multisort program finished\n");
	return 0;
}
