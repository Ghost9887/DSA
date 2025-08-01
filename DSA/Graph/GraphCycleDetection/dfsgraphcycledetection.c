#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { A, B, C, D } Letter;

typedef struct Verticie Verticie;

typedef struct AdjacencyList {
  Verticie *neighbour;
  struct AdjacencyList *next;
} AdjacencyList;

struct Verticie {
  Letter letter;
  AdjacencyList *list;
};

Verticie *createNewVerticie(Letter letter);
void createNewAdjacencyList(Verticie *from, Verticie *to);
void createEdge(Verticie *from, Verticie *to);
void printAdjacencyList(Verticie *v);
void DFS(Verticie *verticie);
void DFSHelper(bool *arr, Verticie *verticie, Verticie *parentVerticie);

bool isCyclic = false;

int main() {

  Verticie *v1 = createNewVerticie(A);
  Verticie *v2 = createNewVerticie(B);
  Verticie *v3 = createNewVerticie(C);
  Verticie *v4 = createNewVerticie(D);
  createEdge(v1, v2);
  createEdge(v2, v3);
  createEdge(v1, v4);
  printf("Starting DFS on Graph 1...\n");
  DFS(v1);
  printf("Graph1 cyclic: %b\n", isCyclic);
  Verticie *v5 = createNewVerticie(A);
  Verticie *v6 = createNewVerticie(B);
  Verticie *v7 = createNewVerticie(C);
  Verticie *v8 = createNewVerticie(D);
  createEdge(v1, v2);
  createEdge(v2, v3);
  createEdge(v3, v4);
  createEdge(v2, v4);
  printf("Starting DFS on Graph 2...\n");
  DFS(v1);
  printf("Graph2 cyclic: %b\n", isCyclic);

  return 0;
}

Verticie *createNewVerticie(Letter letter) {
  Verticie *newVerticie = malloc(sizeof(Verticie));
  newVerticie->letter = letter;
  newVerticie->list = NULL;
  return newVerticie;
}

void createEdge(Verticie *from, Verticie *to) {
  // create the adj list
  createNewAdjacencyList(from, to);
  createNewAdjacencyList(to, from);
}

void createNewAdjacencyList(Verticie *from, Verticie *to) {

  AdjacencyList *newList = malloc(sizeof(AdjacencyList));
  newList->neighbour = to;
  newList->next = NULL;

  if (from->list == NULL) {
    from->list = newList;
    return;
  }

  AdjacencyList *current = from->list;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = newList;
}

void DFS(Verticie *verticie) {
  bool arr[4] = {0};
  DFSHelper(arr, verticie, verticie);
}

void DFSHelper(bool *arr, Verticie *verticie, Verticie *parentVerticie) {
  arr[verticie->letter] = true;
  printf("%c -> ", 'A' + verticie->letter);
  AdjacencyList *current = verticie->list;
  while (current != NULL) {
    if (arr[current->neighbour->letter] == false) {
      DFSHelper(arr, current->neighbour, verticie);
    } else if (arr[current->neighbour->letter] == true &&
               parentVerticie->letter != current->neighbour->letter) {
      isCyclic = true;
    }
    current = current->next;
  }
}
