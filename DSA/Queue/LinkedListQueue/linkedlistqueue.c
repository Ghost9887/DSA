#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct Queue {
  Node *front;
  Node *rear;
} Queue;

Queue *createQueue();
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
void displayQueue(Queue *q);

int main() {
  Queue *q = createQueue();

  enqueue(q, 5);
  enqueue(q, 15);
  enqueue(q, 25);

  displayQueue(q);

  printf("Dequeued: %d\n", dequeue(q));
  displayQueue(q);

  return 0;
}

Queue *createQueue() {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->front = q->rear = NULL;
  return q;
}

void enqueue(Queue *q, int value) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->data = value;
  temp->next = NULL;
  if (q->rear == NULL) {
    q->front = q->rear = temp;
  } else {
    q->rear->next = temp;
    q->rear = temp;
  }
}

int dequeue(Queue *q) {
  if (q->front == NULL) {
    return -1;
  }
  Node *temp = q->front;
  int value = temp->data;
  q->front = q->front->next;
  if (q->front == NULL) {
    q->rear = NULL;
  }
  free(temp);
  return value;
}

void displayQueue(Queue *q) {
  Node *temp = q->front;
  while (temp != NULL) {
    printf("%d -> ", temp->data);
    temp = temp->next;
  }
  printf("NULL\n");
}
