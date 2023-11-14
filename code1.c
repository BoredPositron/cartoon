#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
  int *x = (int *)a;
  int *y = (int *)b;

  return *y - *x;
}

void mergeArrays(int A[], int B[], int C[], int n, int m) {
  int i = 0, j = 0, k = 0; // Initialize indices

  while (i < n && j < m) {
    if (A[i] <= B[j]) {
      C[k++] = B[j++];
    } else {
      C[k++] = A[i++];
    }
  }

  while (i < n) {
    C[k++] = A[i++]; // Copy any remaining elements from A to C
  }

  while (j < m) {
    C[k++] = B[j++]; // Copy any remaining elements from B to C
  }

  /* Sort the merged array in descending order. */
  qsort(C, n + m, sizeof(int), compare);
}

int main() {
  int A[] = {1, 35, 5, 73, 9};
  int B[] = {10, 85, 6, 44, 2};
  int n = sizeof(A) / sizeof(A[0]);
  int m = sizeof(B) / sizeof(B[0]);
  int C[n + m];

  mergeArrays(A, B, C, n, m);

  printf("Merged and sorted (descending) array is: ");
  for (int i = 0; i < n + m; i++) {
    printf("%d ", C[i]);
  }
  printf("\n");

  return 0;
}
