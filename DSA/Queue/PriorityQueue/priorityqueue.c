#include <asm-generic/errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct PriorityQueue {
  Node *front;
  Node *rear;
  int size;
} PriorityQueue;

void enqueue(PriorityQueue *pq, int data);
void dequeue(PriorityQueue *pq);
void peek(PriorityQueue *pq);
void peekRear(PriorityQueue *pq);
void printQueue(PriorityQueue *pq);

int main() {
  PriorityQueue *pq = malloc(sizeof(PriorityQueue));
  pq->front = NULL;
  pq->rear = NULL;
  printf("Starting enqueue\n");
  enqueue(pq, 1);
  enqueue(pq, 5);
  enqueue(pq, 2);
  enqueue(pq, 4);
  enqueue(pq, 6);
  peek(pq);
  peekRear(pq);
  printQueue(pq);
  dequeue(pq);
  peek(pq);
  printQueue(pq);

  return 0;
}

void enqueue(PriorityQueue *pq, int data) {
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;
  printf("Enqueuing: %d\n", data);
  if (pq->front == NULL) {
    pq->front = pq->rear = newNode;
  }

  PriorityQueue *current = pq;

  while (current->front->next != NULL) {
    if (data > current->front->next->data) {
      PriorityQueue *temp = current;
      current->front = current->front->next;
      current->front->next = temp->front;
      pq = current;
      return;
    }
    current->front = current->front->next;
  }
  pq = current;
}

void dequeue(PriorityQueue *q) {
  if (q->front == NULL) {
    return;
  }
  Node *temp = q->front;
  int value = temp->data;
  q->front = q->front->next;
  if (q->front == NULL) {
    q->rear = NULL;
  }
  free(temp);
}

void peek(PriorityQueue *pq) {

  if (pq->front == NULL) {
    printf("Queue is empty!\n");
  }

  printf("peek: %d\n", pq->front->data);
}

void peekRear(PriorityQueue *pq) {
  if (pq->front == NULL) {
    printf("Queue is empty!\n");
  }
  printf("peek rear: %d\n", pq->rear->data);
}

void printQueue(PriorityQueue *pq) {

  if (pq->front == NULL) {
    printf("Queue is empty!\n");
  }

  PriorityQueue *current = pq;
  while (current->front != current->rear) {
    printf("%d -> ", current->front->data);
    current->front = current->front->next;
  }
}
