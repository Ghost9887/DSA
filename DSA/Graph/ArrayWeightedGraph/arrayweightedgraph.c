#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum{
  A,
  B,
  C,
  D
}Letter;

void initializeMatrix(int matrix[4][4]);
void printMatrix(int matrix[4][4]);
void addToGraph(int matrix[4][4], Letter connection1, Letter connection2, int weight);
void deleteFromGraph(int matrix[4][4], Letter connection);

int main(){
  int matrix[4][4];
  initializeMatrix(matrix);
  printMatrix(matrix);
  Letter connection1 = A;
  Letter connection2 = B;
  int weight = 3;
  addToGraph(matrix, connection1, connection2, 3);
  connection1 = A; 
  connection2 = C;
  weight = 2;
  addToGraph(matrix, connection1, connection2, 2);
  connection1 = C;
  connection2 = B;
  weight = 1;
  addToGraph(matrix, connection1, connection2, weight);
  connection1 = D; 
  connection2 = A;
  weight = 4;
  addToGraph(matrix, connection1, connection2, weight);
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

void initializeMatrix(int matrix[4][4]){
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      matrix[i][j] = 0;
    }
  }
}

void addToGraph(int matrix[4][4], Letter connection1, Letter connection2, int weight){
  matrix[connection1][connection2] = weight;

  //adding this make the graph undirected
  //matrix[connection2][connection1] = weight
  
}

void deleteFromGraph(int matrix[4][4], Letter connection){
  for(int i = 0; i < 4; i++){
    matrix[connection][i] = 0;
    matrix[i][connection] = 0;
  }
}

void printMatrix(int matrix[4][4]){
  for(int i = 0; i < 4; i++){
    printf("\n");
    for(int j = 0; j < 4; j++){
      printf("[%d] ", matrix[i][j]);
    }
  }
}
