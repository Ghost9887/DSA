#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { A, B, C, D, E, F, G, H, I } Letter;

typedef struct Vertex Vertex;

typedef struct AdjList {
  Vertex *neighbour;
  int weight;
  struct AdjList *next;
} AdjList;

typedef struct Vertex {
  Letter letter;
  AdjList *list;

  int gCost;
  int hCost;
  int fCost;
  bool visited;

  Vertex *parent;
  struct Vertex *nextInQueue;
} Vertex;

typedef struct {
  Vertex *front;
} PriorityQueue;

Vertex *createNewVertex(Letter letter);
void createEdge(Vertex *from, Vertex *to, int weight);
void createNewAdjList(Vertex *from, Vertex *to, int weight);
void printGraph(Vertex *vertex);
void printPath(Vertex *goal);
int heuristic(Vertex *a, Vertex *b);

PriorityQueue *initializeQueue();
void enqueue(PriorityQueue *pq, Vertex *vertex);
Vertex *dequeue(PriorityQueue *pq);
void printQueue(PriorityQueue *pq);

void astar(Vertex *start, Vertex *goal);

int main() {
  Vertex *v[9];
  for (int i = A; i <= I; i++)
    v[i] = createNewVertex(i);

  createEdge(v[A], v[B], 1);
  createEdge(v[A], v[D], 4);
  createEdge(v[B], v[C], 2);
  createEdge(v[B], v[E], 3);
  createEdge(v[C], v[F], 1);
  createEdge(v[C], v[G], 2);
  createEdge(v[D], v[E], 2);
  createEdge(v[D], v[I], 3);
  createEdge(v[E], v[G], 3);
  createEdge(v[E], v[I], 3);
  createEdge(v[F], v[G], 1);
  createEdge(v[G], v[H], 6);
  createEdge(v[H], v[I], 2);
  createEdge(v[I], v[C], 4);
  createEdge(v[I], v[F], 2);

  for (int i = A; i <= I; i++) {
    printGraph(v[i]);
  }

  astar(v[A], v[H]);

  return 0;
}

Vertex *createNewVertex(Letter letter) {
  Vertex *v = malloc(sizeof(Vertex));
  v->letter = letter;
  v->list = NULL;
  v->gCost = 9999;
  v->hCost = 0;
  v->fCost = 9999;
  v->visited = false;
  v->parent = NULL;
  v->nextInQueue = NULL;
  return v;
}

void createNewAdjList(Vertex *from, Vertex *to, int weight) {
  AdjList *adj = malloc(sizeof(AdjList));
  adj->neighbour = to;
  adj->weight = weight;
  adj->next = NULL;

  if (from->list == NULL) {
    from->list = adj;
  } else {
    AdjList *curr = from->list;
    while (curr->next != NULL)
      curr = curr->next;
    curr->next = adj;
  }
}

void createEdge(Vertex *from, Vertex *to, int weight) {
  createNewAdjList(from, to, weight);
}

PriorityQueue *initializeQueue() {
  PriorityQueue *pq = malloc(sizeof(PriorityQueue));
  pq->front = NULL;
  return pq;
}

void enqueue(PriorityQueue *pq, Vertex *vertex) {
  if (pq->front == NULL || vertex->fCost < pq->front->fCost) {
    vertex->nextInQueue = pq->front;
    pq->front = vertex;
    return;
  }

  Vertex *current = pq->front;
  while (current->nextInQueue != NULL &&
         current->nextInQueue->fCost <= vertex->fCost) {
    current = current->nextInQueue;
  }

  vertex->nextInQueue = current->nextInQueue;
  current->nextInQueue = vertex;
}

Vertex *dequeue(PriorityQueue *pq) {
  if (pq->front == NULL)
    return NULL;
  Vertex *v = pq->front;
  pq->front = pq->front->nextInQueue;
  v->nextInQueue = NULL;
  return v;
}

void astar(Vertex *start, Vertex *goal) {
  start->gCost = 0;
  start->hCost = heuristic(start, goal);
  start->fCost = start->hCost;

  PriorityQueue *pq = initializeQueue();
  enqueue(pq, start);

  while (pq->front != NULL) {
    Vertex *current = dequeue(pq);
    current->visited = true;

    if (current == goal) {
      printf("Path found:\n");
      printPath(goal);
      return;
    }

    AdjList *adj = current->list;
    while (adj != NULL) {
      Vertex *neighbor = adj->neighbour;

      if (neighbor->visited) {
        adj = adj->next;
        continue;
      }

      int tentativeG = current->gCost + adj->weight;
      if (tentativeG < neighbor->gCost) {
        neighbor->parent = current;
        neighbor->gCost = tentativeG;
        neighbor->hCost = heuristic(neighbor, goal);
        neighbor->fCost = neighbor->gCost + neighbor->hCost;
        enqueue(pq, neighbor);
      }
      adj = adj->next;
    }
  }

  printf("No path found.\n");
}

int heuristic(Vertex *a, Vertex *b) {
  // Simple placeholder heuristic: absolute difference in letter value
  return a->letter - b->letter;
}

void printPath(Vertex *goal) {
  if (goal->parent != NULL) {
    printPath(goal->parent);
  }
  printf("%c \n", 'A' + goal->letter);
}

void printGraph(Vertex *vertex) {
  printf("Neighbours of %c: ", 'A' + vertex->letter);
  AdjList *current = vertex->list;
  while (current != NULL) {
    printf("(%d) %c ", current->weight, 'A' + current->neighbour->letter);
    current = current->next;
  }
  printf("\n");
}
