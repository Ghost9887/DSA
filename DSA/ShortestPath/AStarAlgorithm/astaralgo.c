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
} Vertex;

typedef struct {
  Vertex *front;
  Vertex *rear;
} PriorityQueue;

Vertex *createNewVertex(Letter letter);
void createNewAdjList(Vertex *from, Vertex *to, int weight);
void createEdge(Vertex *from, Vertex *to, int weight);
void printGraph(Vertex *Verticie);
PriorityQueue *initializeQueue();
void enqueue(PriorityQueue *pq, Vertex *vertex);
void dequeue(PriorityQueue *pq);
void peek(PriorityQueue *pq);
void printQueue(PriorityQueue *pq);

int main() {
  Vertex *vA = createNewVertex(A);
  Vertex *vB = createNewVertex(B);
  Vertex *vC = createNewVertex(C);
  Vertex *vD = createNewVertex(D);
  Vertex *vE = createNewVertex(E);
  Vertex *vF = createNewVertex(F);
  Vertex *vG = createNewVertex(G);
  Vertex *vH = createNewVertex(H);
  Vertex *vI = createNewVertex(I);

  createEdge(vA, vB, 1);
  createEdge(vA, vD, 4);
  createEdge(vB, vC, 2);
  createEdge(vB, vE, 3);
  createEdge(vC, vF, 1);
  createEdge(vC, vG, 2);
  createEdge(vD, vE, 2);
  createEdge(vD, vI, 3);
  createEdge(vE, vG, 3);
  createEdge(vE, vI, 3);
  createEdge(vF, vG, 1);
  createEdge(vG, vH, 6);
  createEdge(vH, vI, 2);
  createEdge(vI, vC, 4); // Optional cycle
  createEdge(vI, vF, 2); // Shortcut
  printGraph(vA);
  printGraph(vB);
  printGraph(vC);
  printGraph(vD);
  printGraph(vE);
  printGraph(vF);
  printGraph(vG);
  printGraph(vH);
  printGraph(vI);

  PriorityQueue *pq = initializeQueue();
  enqueue(pq, vA);
  enqueue(pq, vB);
  printQueue(pq);

  return 0;
}

PriorityQueue *initializeQueue() {
  PriorityQueue *pq = malloc(sizeof(PriorityQueue));
  pq->front = NULL;
  pq->rear = NULL;
  return pq;
}

void enqueue(PriorityQueue *pq, Vertex *vertex) {

  if (pq->front == NULL) {
    pq->front = pq->rear = vertex;
  }

  if (vertex->list->weight > pq->front->list->weight) {
    vertex->list->next = pq->front->list;
    pq->front = vertex;
  }

  Vertex *current = pq->front;
  while (current->list->next != NULL &&
         current->list->next->weight >= current->list->weight) {
    current->list = current->list->next;
  }

  vertex->list->next = current->list->next;
  current->list->next = vertex->list;

  if (vertex->list->next == NULL) {
    pq->rear = vertex;
  }
}

void dequeue(PriorityQueue *pq) {

  if (pq->front == NULL) {
    printf("Queue is empty!\n");
  }

  pq->front->list = pq->front->list->next;

  if (pq->front == NULL) {
    pq->rear = pq->front;
  }
}

void peek(PriorityQueue *pq) {

  if (pq->front == NULL) {
    printf("Queue is empty!\n");
  }

  printf("Peek: %c", 'A' + pq->front->letter);
}

void printQueue(PriorityQueue *pq) {
  if (pq->front == NULL) {
    printf("Queue is empty!\n");
    return;
  }
  Vertex *current = pq->front;
  printf("Queue: ");
  while (current != NULL) {
    printf("%c -> ", 'A' + current->letter);
    current->list = current->list->next;
  }
  printf("NULL\n");
}

Vertex *createNewVertex(Letter letter) {
  Vertex *newVertex = malloc(sizeof(Vertex));
  newVertex->letter = letter;
  newVertex->list = NULL;
  return newVertex;
}

void createNewAdjList(Vertex *from, Vertex *to, int weight) {
  AdjList *newAdjList = malloc(sizeof(AdjList));
  newAdjList->neighbour = to;
  newAdjList->next = NULL;
  newAdjList->weight = weight;

  if (from->list == NULL) {
    from->list = newAdjList;
    return;
  }

  AdjList *current = from->list;
  while (current->next != NULL) {
    current = current->next;
  }
  from->list->next = newAdjList;
}

void createEdge(Vertex *from, Vertex *to, int weight) {
  createNewAdjList(from, to, weight);
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
