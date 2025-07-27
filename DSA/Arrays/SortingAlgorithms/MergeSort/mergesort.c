#include <stdio.h>
#include <time.h>

void merge(int arr[], int left, int mid, int right) {
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;

  // Create temporary arrays
  int leftArr[n1], rightArr[n2];

  // Copy data to temporary arrays
  for (i = 0; i < n1; i++)
    leftArr[i] = arr[left + i];
  for (j = 0; j < n2; j++)
    rightArr[j] = arr[mid + 1 + j];

  // Merge the temporary arrays back into arr[left..right]
  i = 0;
  j = 0;
  k = left;
  while (i < n1 && j < n2) {
    if (leftArr[i] <= rightArr[j]) {
      arr[k] = leftArr[i];
      i++;
    } else {
      arr[k] = rightArr[j];
      j++;
    }
    k++;
  }

  // Copy the remaining elements of leftArr[], if any
  while (i < n1) {
    arr[k] = leftArr[i];
    i++;
    k++;
  }

  // Copy the remaining elements of rightArr[], if any
  while (j < n2) {
    arr[k] = rightArr[j];
    j++;
    k++;
  }
}

// The subarray to be sorted is in the index range [left-right]
void mergeSort(int arr[], int left, int right) {
  if (left < right) {

    // Calculate the midpoint
    int mid = left + (right - left) / 2;

    // Sort first and second halves
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // Merge the sorted halves
    merge(arr, left, mid, right);
  }
}

void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d", arr[i]);
  }
}

int main() {

  int arr[] = {
      0, 3, 1, 4, 7, 8, 9, 2, 5, 6, 5, 2, 6, 1, 9, 3, 0, 7, 8, 4, 8, 4, 7, 0, 6,
      9, 5, 1, 3, 2, 1, 9, 3, 5, 0, 7, 6, 4, 2, 8, 4, 6, 8, 2, 0, 5, 3, 9, 1, 7,
      9, 0, 5, 6, 2, 8, 4, 7, 3, 1, 7, 1, 4, 3, 6, 0, 9, 2, 8, 5, 6, 3, 0, 1, 8,
      7, 5, 2, 9, 4, 2, 8, 7, 9, 1, 0, 6, 4, 5, 3, 3, 7, 5, 9, 4, 8, 1, 6, 0, 2,
      5, 9, 2, 4, 3, 0, 7, 6, 1, 8, 0, 6, 1, 5, 8, 2, 9, 4, 7, 3, 8, 1, 6, 3, 0,
      4, 5, 9, 2, 7, 7, 5, 4, 2, 8, 1, 0, 6, 9, 3, 4, 0, 8, 9, 6, 5, 3, 2, 1, 7,
      6, 7, 3, 2, 5, 8, 0, 1, 9, 4, 9, 2, 0, 7, 1, 3, 4, 6, 8, 5, 1, 4, 6, 3, 2,
      0, 5, 8, 7, 9, 2, 5, 7, 8, 0, 1, 9, 3, 4, 6, 3, 8, 9, 1, 6, 2, 5, 4, 7, 0,
      5, 0, 1, 4, 8, 6, 2, 3, 7, 9, 6, 9, 4, 7, 0, 5, 8, 2, 1, 3, 0, 3, 2, 6, 1,
      5, 9, 7, 8, 4, 8, 7, 1, 9, 4, 0, 3, 6, 5, 2, 9, 4, 5, 8, 2, 7, 1, 0, 3, 6,
      1, 2, 8, 0, 3, 7, 6, 9, 5, 4, 7, 6, 9, 5, 0, 4, 3, 1, 2, 8, 3, 0, 6, 7, 8,
      1, 4, 9, 2, 5, 4, 5, 0, 2, 9, 3, 1, 7, 6, 8, 2, 9, 1, 4, 6, 7, 3, 5, 0, 8,
      1, 8, 3, 9, 5, 4, 6, 0, 7, 2, 6, 2, 7, 1, 0, 8, 5, 9, 3, 4, 0, 1, 9, 6, 5,
      3, 8, 4, 2, 7, 9, 8, 0, 3, 7, 2, 6, 1, 4, 5, 5, 1, 3, 7, 4, 0, 9, 6, 2, 8,
      8, 6, 2, 4, 1, 5, 0, 9, 7, 3, 7, 0, 6, 5, 8, 9, 2, 4, 1, 3, 4, 3, 7, 2, 5,
      1, 6, 8, 0, 9, 2, 7, 8, 5, 0, 6, 9, 3, 1, 4, 1, 6, 0, 9, 2, 7, 4, 5, 8, 3,
      3, 5, 1, 8, 6, 4, 2, 0, 9, 7, 6, 0, 9, 1, 8, 3, 7, 2, 5, 4, 5, 4, 8, 2, 7,
      0, 1, 6, 3, 9, 9, 1, 6, 3, 4, 7, 5, 8, 0, 2, 0, 2, 5, 6, 7, 9, 3, 1, 8, 4,
      4, 7, 2, 3, 9, 1, 0, 5, 6, 8, 8, 3, 6, 0, 1, 5, 7, 4, 9, 2, 2, 9, 0, 4, 5,
      3, 8, 7, 6, 1, 1, 7, 3, 8, 6, 9, 2, 0, 4, 5, 6, 5, 8, 1, 0, 2, 9, 3, 7, 4,
      3, 4, 9, 0, 6, 7, 1, 5, 2, 8, 5, 8, 4, 6, 9, 7, 3, 2, 0, 1, 7, 2, 0, 1, 5,
      8, 4, 3, 9, 6, 9, 6, 2, 8, 3, 1, 0, 7, 5, 4, 0, 3, 8, 6, 1, 7, 5, 2, 9, 4,
      4, 1, 5, 9, 2, 0, 6, 3, 8, 7};

  int n = sizeof(arr) / sizeof(arr[0]);

  printf("Before merge sort: ");
  printArray(arr, n);
  printf("\n");

  clock_t t;
  t = clock();

  mergeSort(arr, 0, n - 1);

  t = clock() - t;
  double time_taken = ((double)t) / CLOCKS_PER_SEC;

  printf("After merge sort: ");
  printArray(arr, n);
  printf("\n");

  printf("Time: %f\n", time_taken);
  return 0;
}
