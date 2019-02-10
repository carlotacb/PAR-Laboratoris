#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <tareador.h>

// N and MIN must be powers of 2
long N;
long MIN_SORT_SIZE;
long MIN_MERGE_SIZE;

#define BLOCK_SIZE 128L

#define T int

void basicsort(long n, T data[n]);

void basicmerge(long n, T left[n], T right[n], T result[n*2], long start, long length);

void merge(long n, T left[n], T right[n], T result[n*2], long start, long length) {
        if (length < MIN_MERGE_SIZE*2L) {
                // Base case
                basicmerge(n, left, right, result, start, length);
        } else {
                // Recursive decomposition
		tareador_start_task("Fourth merge call");  
                merge(n, left, right, result, start, length/2);
		tareador_end_task("Fourth merge call"); 
		tareador_start_task("Fifth merge call"); 
                merge(n, left, right, result, start + length/2, length/2);
		tareador_end_task("Fifth merge call"); 
        }
}

void multisort(long n, T data[n], T tmp[n]) {
        if (n >= MIN_SORT_SIZE*4L) {
                // Recursive decomposition
		tareador_start_task("First multisort call");
                multisort(n/4L, &data[0], &tmp[0]);
		tareador_end_task("First multisort call");
		tareador_start_task("Second multisort call");
                multisort(n/4L, &data[n/4L], &tmp[n/4L]);
		tareador_end_task("Second multisort call");
		tareador_start_task("Third multisort call");
                multisort(n/4L, &data[n/2L], &tmp[n/2L]);
		tareador_end_task("Third multisort call");
		tareador_start_task("Fourth multisort call");                
		multisort(n/4L, &data[3L*n/4L], &tmp[3L*n/4L]);
		tareador_end_task("Fourth multisort call");		

		tareador_start_task("First merge call");  
                merge(n/4L, &data[0], &data[n/4L], &tmp[0], 0, n/2L);
		tareador_end_task("First merge call");
		tareador_start_task("Second merge call"); 
                merge(n/4L, &data[n/2L], &data[3L*n/4L], &tmp[n/2L], 0, n/2L);
		tareador_end_task("Second merge call");
		
		tareador_start_task("Third merge call");
                merge(n/2L, &tmp[0], &tmp[n/2L], &data[0], 0, n);
		tareador_end_task("Third merge call");
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
	
	initialize(N, data);
	clear(N, tmp);

	tareador_ON();
   	multisort(N, data, tmp);
	tareador_OFF();

   	check_sorted (N, data);

    	fprintf(stdout, "Multisort program finished\n");
	return 0;
}
