#include <stdio.h>
#include <stdlib.h>

// N and MIN_BS must be powers of 2
extern long N;
extern long MIN_SORT_SIZE;
extern long MIN_MERGE_SIZE;

#define T int

//int qsort_helper(const void *a, const void *b) {
//	T *realA = (T *)a;
//	T *realB = (T *)b;
//	return *realA - *realB;
//}

void bubble_sort(int a[], int array_size) {
   int i, j, temp;
   for (i = 0; i < (array_size - 1); ++i) {
      for (j = 0; j < array_size - 1 - i; ++j ) {
         if (a[j] > a[j+1]) {
            temp = a[j+1];
            a[j+1] = a[j];
            a[j] = temp;
         }
      }
   }
}


void basicsort(long n, T data[n]) {
	//printf("Sort n=%ld, %x\n\n", n, data);
	//qsort(data, n, sizeof(T), qsort_helper);
        bubble_sort(data, n);
}

static inline int pivots_are_aligned(T *left, T *right, long n, long leftStart, long rightStart) {
	if (leftStart == 0 || rightStart == 0 || leftStart == n || rightStart == n) {
		return 1;
	}
	
	if (left[leftStart] <= right[rightStart] && right[rightStart-1] <= left[leftStart]) {
		return 1;
	}
	if (right[rightStart] <= left[leftStart] && left[leftStart-1] <= right[rightStart]) {
		return 1;
	}
	
	return 0;
}

static inline int must_decrease_left(T *left, T *right, long n, long leftStart, long rightStart) {
	return (left[leftStart] > right[rightStart]);
}

static inline long min(long a, long b) {
	if (a < b) {
		return a;
	} else {
		return b;
	}
}

static inline void find_pivot(T *left, T *right, long n, long start, long *leftStart, long *rightStart) {
	
	if (start == 0) {
	   *leftStart = 0;
	   *rightStart = 0;
           return;
	}
	
        int jumpSize;
        *leftStart = start/2L;
        *rightStart = start/2L;
        jumpSize = min(start/2L, n - start/2L) / 2L;

	while (1) {
		if (pivots_are_aligned(left, right, n, *leftStart, *rightStart)) {
			return;
		} else if (must_decrease_left(left, right, n, *leftStart, *rightStart)) {
			*leftStart -= jumpSize;
			*rightStart += jumpSize;
		} else {
			*rightStart -= jumpSize;
			*leftStart += jumpSize;
		}
                jumpSize = jumpSize/2L;
                if (jumpSize==0) jumpSize=1;
	}
}

void basicmerge(long n, T left[n], T right[n], T result[n*2], long start, long length) {
	long leftStart, rightStart;
	find_pivot(left, right, n, start, &leftStart, &rightStart);
	
	result += start;
	while (length != 0) {
		if (leftStart == n) {
			*result = right[rightStart];
			rightStart++;
			result++;
		} else if (rightStart == n) {
			*result = left[leftStart];
			leftStart++;
			result++;
		} else if (left[leftStart] <= right[rightStart]) {
			*result = left[leftStart];
			leftStart++;
			result++;
		} else {
			*result = right[rightStart];
			rightStart++;
			result++;
		}
		length--;
	}
}
