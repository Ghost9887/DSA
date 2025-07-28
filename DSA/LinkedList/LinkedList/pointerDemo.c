#include <stdio.h>
#include <stdlib.h>

void updatePointer(int *ptr);

int main() {

  int *ptr = malloc(sizeof(int));

  *ptr = 5;

  printf("Old Value: %d\n", *ptr);

  updatePointer(ptr);

  printf("New Value: %d\n", *ptr);

  return 0;
}

void updatePointer(int *ptr) { *ptr = 10; }
