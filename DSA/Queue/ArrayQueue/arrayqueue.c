#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

typedef struct Queue {
  int items[SIZE];
  int front;
  int rear;
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
  q->front = q->rear = -1;
  return q;
}

void enqueue(Queue *q, int value) {
  if (q->rear == SIZE - 1) {
    printf("Queue overflow\n");
    return;
  }
  if (q->front == -1)
    q->front = 0;
  q->items[++q->rear] = value;
}

int dequeue(Queue *q) {
  if (q->front == -1 || q->front > q->rear) {
    printf("Queue underflow\n");
    return -1;
  }
  return q->items[q->front++];
}

void displayQueue(Queue *q) {
  if (q->front == -1 || q->front > q->rear) {
    printf("Queue is empty\n");
    return;
  }
  for (int i = q->front; i <= q->rear; i++)
    printf("%d -> ", q->items[i]);
  printf("NULL\n");
}
