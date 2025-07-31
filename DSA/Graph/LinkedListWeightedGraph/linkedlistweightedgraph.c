#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>

typedef enum { A, B, C, D } Letter;

typedef struct Verticie Verticie;

typedef struct AdjacencyList {
  Verticie *neighbour;
  int weight;
  struct AdjacencyList *next;
} AdjacencyList;

struct Verticie {
  Letter letter;
  AdjacencyList *list;
};

Verticie *createNewVerticie(Letter letter);
void createNewAdjacencyList(Verticie *from, Verticie *to, int weight);
void createEdge(Verticie *from, Verticie *to, int weight);
void printAdjacencyList(Verticie *v);

int main() {

  Verticie *v1 = createNewVerticie(A);
  Verticie *v2 = createNewVerticie(B);
  Verticie *v3 = createNewVerticie(C);
  Verticie *v4 = createNewVerticie(D);
  createEdge(v1, v2, 2);
  createEdge(v2, v3, 1);
  createEdge(v1, v4, 3);
  printAdjacencyList(v1);
  printAdjacencyList(v2);
  printAdjacencyList(v3);
  printAdjacencyList(v4);

  return 0;
}

Verticie *createNewVerticie(Letter letter) {
  Verticie *newVerticie = malloc(sizeof(Verticie));
  newVerticie->letter = letter;
  newVerticie->list = NULL;
  return newVerticie;
}

void createEdge(Verticie *from, Verticie *to, int weight) {
  // create the adj list
  createNewAdjacencyList(from, to, weight);
  createNewAdjacencyList(to, from, weight);
}

void createNewAdjacencyList(Verticie *from, Verticie *to, int weight) {

  AdjacencyList *newList = malloc(sizeof(AdjacencyList));
  newList->neighbour = to;
  newList->next = NULL;
  newList->weight = weight;

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

void printAdjacencyList(Verticie *v) {
  printf("Neighbours of %c: ", 'A' + v->letter);
  AdjacencyList *current = v->list;
  while (current != NULL) {
    printf("%c (%d) ", 'A' + current->neighbour->letter, current->weight);
    current = current->next;
  }
  printf("\n");
}
