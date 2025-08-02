#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { A, B, C, D } Letter;

typedef struct Vertex Vertex;

typedef struct AdjacencyList {
  Vertex *neighbour;
  struct AdjacencyList *next;
} AdjacencyList;

struct Vertex {
  Letter letter;
  AdjacencyList *list;
};

typedef struct Node {
  Vertex *vertex;
  struct Node *next;
} Node;

typedef struct {
  Node *front;
  Node *rear;
  Node *next;
} Queue;

Vertex *createNewVertex(Letter letter);
void createNewAdjacencyList(Vertex *from, Vertex *to);
void createEdge(Vertex *from, Vertex *to);
void printAdjacencyList(Vertex *v);
void DFSHelper(bool *arr, Vertex *vertex);
void DFS(Vertex *vertex);
Queue *createQueue();
void enqueue(Queue *q, Vertex *vertex);
Vertex *dequeue(Queue *q);
void isEmpty();
void printQueue(Queue *q);
void BFS(Queue *q, Vertex *vertex);

int main() {

  Vertex *v1 = createNewVertex(A);
  Vertex *v2 = createNewVertex(B);
  Vertex *v3 = createNewVertex(C);
  Vertex *v4 = createNewVertex(D);
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

Vertex *createNewVertex(Letter letter) {
  Vertex *newVertex = malloc(sizeof(Vertex));
  newVertex->letter = letter;
  newVertex->list = NULL;
  return newVertex;
}

void createEdge(Vertex *from, Vertex *to) {
  // create the adj list
  createNewAdjacencyList(from, to);
  createNewAdjacencyList(to, from);
}

void createNewAdjacencyList(Vertex *from, Vertex *to) {

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

void DFS(Vertex *vertex) {

  bool arr[4] = {0};
  DFSHelper(arr, vertex);
}

void DFSHelper(bool *arr, Vertex *vertex) {

  arr[vertex->letter] = true;
  printf("%c -> ", 'A' + vertex->letter);

  AdjacencyList *current = vertex->list;

  while (current != NULL) {
    if (arr[current->neighbour->letter] == false) {
      DFSHelper(arr, current->neighbour);
    }
    current = current->next;
  }
}

void BFS(Queue *q, Vertex *start) {
  bool visited[4] = {false};
  enqueue(q, start);
  visited[start->letter] = true;

  while (q->front != NULL) {
    Vertex *currentVert = dequeue(q);
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

void enqueue(Queue *q, Vertex *vertex) {

  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->vertex = vertex;
  newNode->next = NULL;

  if (q->rear == NULL) {
    q->front = q->rear = newNode;
  } else {
    q->rear->next = newNode;
    q->rear = newNode;
  }
}
Vertex *dequeue(Queue *q) {
  if (q->front == NULL)
    return NULL;

  Node *temp = q->front;
  Vertex *v = temp->vertex;
  q->front = q->front->next;
  if (q->front == NULL)
    q->rear = NULL;
  free(temp);
  return v;
}

void printAdjacencyList(Vertex *v) {
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
    printf("%d -> ", temp->vertex->letter);
    temp = temp->next;
  }
}
