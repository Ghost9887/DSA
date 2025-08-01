#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { A, B, C, D } Letter;

typedef struct Verticie Verticie;

typedef struct AdjList {
  Verticie *neighbour;
  Verticie *current;
  int weight;
  struct AdjList *next;
} AdjList;

typedef struct Verticie {
  Letter letter;
  int distance; // used for the dijkstras algo
  bool visited; // used for the dijkstras algo
  AdjList *list;
} Verticie;

// global variables
// keep track of all the verticies
Verticie *arr[3];
int count = 0;

Verticie *createNewVerticie(Letter letter);
void createNewList(Verticie *from, Verticie *to, int weight);
void createEdge(Verticie *from, Verticie *to, int weight);
void printGraph(Verticie *verticie);
void dijkstrasAlgo(Verticie *start, Verticie *targetVerticie);

int main() {

  Verticie *v1 = createNewVerticie(A);
  Verticie *v2 = createNewVerticie(B);
  Verticie *v3 = createNewVerticie(C);
  // Verticie *v4 = createNewVerticie(D);
  createEdge(v1, v2, 2);
  createEdge(v2, v3, 3);
  createEdge(v1, v3, 6);

  printGraph(v1);
  printGraph(v2);
  printGraph(v3);

  dijkstrasAlgo(v1, v3);

  return 0;
}

void dijkstrasAlgo(Verticie *start, Verticie *target) {
  start->distance = 0;
  while (true) {
    Verticie *current = NULL;
    int minDist = INT_MAX;
    for (int i = 0; i < count; i++) {
      if (!arr[i]->visited && arr[i]->distance < minDist) {
        minDist = arr[i]->distance;
        current = arr[i];
      }
    }
    if (current == NULL) {
      break;
    }
    current->visited = true;
    if (current == target) {
      break;
    }
    AdjList *adj = current->list;
    while (adj != NULL) {
      Verticie *neighbor = adj->neighbour;
      if (!neighbor->visited) {
        int newDist = current->distance + adj->weight;
        if (newDist < neighbor->distance) {
          neighbor->distance = newDist;
        }
      }
      adj = adj->next;
    }
  }
  if (target->distance != INT_MAX) {
    printf("Shortest distance from %c to %c: %d\n", 'A' + start->letter,
           'A' + target->letter, target->distance);
  } else {
    printf("No path found from %c to %c.\n", 'A' + start->letter,
           'A' + target->letter);
  }
}

Verticie *createNewVerticie(Letter letter) {
  Verticie *newVerticie = malloc(sizeof(Verticie));
  newVerticie->letter = letter;
  newVerticie->list = NULL;
  newVerticie->visited = false;
  newVerticie->distance = INT_MAX; // set the distance to infinity
  arr[count] = newVerticie;
  count++;
  return newVerticie;
}

void createNewList(Verticie *from, Verticie *to, int weight) {
  AdjList *newList = malloc(sizeof(AdjList));
  newList->neighbour = to;
  newList->weight = weight;
  newList->next = NULL;
  newList->current = from;

  if (from->list == NULL) {
    from->list = newList;
    return;
  }
  AdjList *current = from->list;
  while (current->next != NULL) {
    current = current->next;
  }
  from->list->next = newList;
}

void createEdge(Verticie *from, Verticie *to, int weight) {

  // directed graph with weight
  createNewList(from, to, weight);
}

void printGraph(Verticie *verticie) {
  printf("Neighbours of %c: ", 'A' + verticie->letter);
  AdjList *current = verticie->list;
  while (current != NULL) {
    printf("%c (%d) ", 'A' + current->neighbour->letter, current->weight);
    current = current->next;
  }
  printf("\n");
}
