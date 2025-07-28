#include <stdio.h>

int binarySearch(int arr[], int target, int size);
void generateArray(int arr[], int length);

int NUMBEROFOPERATIONS = 0;

int main() {

  int arr[500];
  generateArray(arr, 500);
  int size = sizeof(arr) / sizeof(arr[0]);
  int target = 494;

  printf("Target found at: %d\n", binarySearch(arr, target, size));
  printf("Number of operations: %d\n", NUMBEROFOPERATIONS);

  return 0;
}

int binarySearch(int arr[], int target, int size) {
  int low = 0, high = size - 1;

  while (low <= high) {
    NUMBEROFOPERATIONS++;
    int mid = low + (high - low) / 2;

    if (arr[mid] == target)
      return mid;
    else if (target < arr[mid])
      high = mid - 1;
    else
      low = mid + 1;
  }

  return -1;
}

void generateArray(int arr[], int length) {

  for (int i = 0; i < length; i++) {
    arr[i] = i;
  }
}
