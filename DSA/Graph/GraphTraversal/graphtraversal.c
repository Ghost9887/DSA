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

typedef struct Node {
  Verticie *verticie;
  struct Node *next;
} Node;

typedef struct {
  Node *front;
  Node *rear;
  Node *next;
} Queue;

Verticie *createNewVerticie(Letter letter);
void createNewAdjacencyList(Verticie *from, Verticie *to);
void createEdge(Verticie *from, Verticie *to);
void printAdjacencyList(Verticie *v);
void DFSHelper(bool *arr, Verticie *verticie);
void DFS(Verticie *verticie);
Queue *createQueue();
void enqueue(Queue *q, Verticie *verticie);
Verticie *dequeue(Queue *q);
void isEmpty();
void printQueue(Queue *q);
void BFS(Queue *q, Verticie *verticie);

int main() {

  Verticie *v1 = createNewVerticie(A);
  Verticie *v2 = createNewVerticie(B);
  Verticie *v3 = createNewVerticie(C);
  Verticie *v4 = createNewVerticie(D);
  createEdge(v1, v2);
  createEdge(v2, v3);
  createEdge(v1, v4);
  printAdjacencyList(v1);
  printAdjacencyList(v2);
  printAdjacencyList(v3);
  printAdjacencyList(v4);

  printf("\n");
  printf("Starting DFS...\n");
  DFS(v1);
  printf("\n");
  printf("\n");
  Queue *q = createQueue();
  printf("Starting BFS...\n");
  BFS(q, v1);
  printf("\n");

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
  DFSHelper(arr, verticie);
}

void DFSHelper(bool *arr, Verticie *verticie) {

  arr[verticie->letter] = true;
  printf("%c -> ", 'A' + verticie->letter);

  AdjacencyList *current = verticie->list;

  while (current != NULL) {
    if (arr[current->neighbour->letter] == false) {
      DFSHelper(arr, current->neighbour);
    }
    current = current->next;
  }
}

void BFS(Queue *q, Verticie *start) {
  bool visited[4] = {false};
  enqueue(q, start);
  visited[start->letter] = true;

  while (q->front != NULL) {
    Verticie *currentVert = dequeue(q);
    printf("%c -> ", 'A' + currentVert->letter);
    AdjacencyList *neighbor = currentVert->list;

    while (neighbor != NULL) {
      int idx = neighbor->neighbour->letter;
      if (!visited[idx]) {
        visited[idx] = true;
        enqueue(q, neighbor->neighbour);
      }
      neighbor = neighbor->next;
    }
  }
}

Queue *createQueue() {
  Queue *q = malloc(sizeof(Queue));
  q->front = NULL;
  q->rear = NULL;
  return q;
}

void enqueue(Queue *q, Verticie *verticie) {

  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->verticie = verticie;
  newNode->next = NULL;

  if (q->rear == NULL) {
    q->front = q->rear = newNode;
  } else {
    q->rear->next = newNode;
    q->rear = newNode;
  }
}
Verticie *dequeue(Queue *q) {
  if (q->front == NULL)
    return NULL;

  Node *temp = q->front;
  Verticie *v = temp->verticie;
  q->front = q->front->next;
  if (q->front == NULL)
    q->rear = NULL;
  free(temp);
  return v;
}

void printAdjacencyList(Verticie *v) {
  printf("Neighbours of %c: ", 'A' + v->letter);
  AdjacencyList *current = v->list;
  while (current != NULL) {
    printf("%c ", 'A' + current->neighbour->letter);
    current = current->next;
  }
  printf("\n");
}

void printQueue(Queue *q) {
  if (q->front == NULL) {
    printf("Queue is empty!\n");
    return;
  }
  Node *temp = q->front;
  while (temp != NULL) {
    printf("%d -> ", temp->verticie->letter);
    temp = temp->next;
  }
}
