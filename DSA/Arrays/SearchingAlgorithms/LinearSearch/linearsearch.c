#include <stdio.h>
#include <time.h>

void linearSearch(int arr[], int size, int target);
void generateArray(int arr[], int length);

int main() {

  int arr[500];

  generateArray(arr, 500);

  int size = sizeof(arr) / sizeof(arr[0]);

  int target = 494;
  printf("Target: %d\n", target);

  clock_t t;
  t = clock();

  linearSearch(arr, size, target);

  t = clock() - t;
  double time_taken = ((double)t) / CLOCKS_PER_SEC;

  printf("Time: %f\n", time_taken);

  return 0;
}

void generateArray(int arr[], int length) {
  for (int i = 0; i < length; i++) {
    arr[i] = i;
  }
}

void linearSearch(int arr[], int size, int target) {

  for (int i = 0; i < size; i++) {
    if (arr[i] == target) {
      printf("Found target at index: %d\n", i);
    }
  }
}
