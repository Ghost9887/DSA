#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { A, B, C, D } Letter;

void initializeMatrix(int matrix[4][4]);
void printMatrix(int matrix[4][4]);
void addToGraph(int matrix[4][4], Letter connection1, Letter connection2);
void deleteFromGraph(int matrix[4][4], Letter connection);

int main() {
  int matrix[4][4];
  initializeMatrix(matrix);
  printMatrix(matrix);
  Letter connection1 = A;
  Letter connection2 = B;
  addToGraph(matrix, connection1, connection2);
  connection1 = C;
  connection2 = A;
  addToGraph(matrix, connection1, connection2);
  connection1 = C;
  connection2 = B;
  addToGraph(matrix, connection1, connection2);
  connection1 = A;
  connection2 = D;
  addToGraph(matrix, connection1, connection2);
  printf("\n");
  printf("\n");
  printMatrix(matrix);
  printf("\n");
  printf("\n");
  connection1 = C;
  deleteFromGraph(matrix, connection1);
  printMatrix(matrix);
  return 0;
}

void initializeMatrix(int matrix[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix[i][j] = 0;
    }
  }
}

void addToGraph(int matrix[4][4], Letter connection1, Letter connection2) {
  matrix[connection1][connection2] = 1;

  // removing this make it a directed graph
  matrix[connection2][connection1] = 1;
}

void deleteFromGraph(int matrix[4][4], Letter connection) {
  for (int i = 0; i < 4; i++) {
    matrix[connection][i] = 0;
    matrix[i][connection] = 0;
  }
}

void printMatrix(int matrix[4][4]) {
  for (int i = 0; i < 4; i++) {
    printf("\n");
    for (int j = 0; j < 4; j++) {
      printf("[%d] ", matrix[i][j]);
    }
  }
}
