#include <stdio.h>
#include <time.h>

void linearSearch(int arr[], int size, int target);
void generateArray(int arr[], int length);

int NUMBEROFOPERATIONS = 0;

int main() {

  int arr[500];

  generateArray(arr, 500);

  int size = sizeof(arr) / sizeof(arr[0]);

  int target = 494;
  printf("Target: %d\n", target);

  linearSearch(arr, size, target);

  printf("Number of operations: %d\n", NUMBEROFOPERATIONS);

  return 0;
}

void generateArray(int arr[], int length) {
  for (int i = 0; i < length; i++) {
    arr[i] = i;
  }
}

void linearSearch(int arr[], int size, int target) {
  for (int i = 0; i < size; i++) {
    NUMBEROFOPERATIONS++;
    if (arr[i] == target) {
      printf("Found target at index: %d\n", i);
      break;
    }
  }
}
