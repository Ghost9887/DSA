#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *push(Node *head, int data);
Node *pop(Node *head);
void peek(Node *head);
bool isEmpty(Node *head);

int main() {
  Node *stack = NULL;

  stack = push(stack, 1);
  stack = push(stack, 2);
  stack = push(stack, 3);
  peek(stack);
  stack = pop(stack);
  peek(stack);

  if (isEmpty(stack)) {
    printf("The stack is currently empty.\n");
  } else {
    printf("The stack is not empty.\n");
  }

  stack = pop(stack);
  stack = pop(stack);

  if (isEmpty(stack)) {
    printf("The stack is currently empty.\n");
  }

  return 0;
}

Node *push(Node *head, int data) {
  Node *newNode = malloc(sizeof(Node));
  if (!newNode) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }
  newNode->data = data;
  newNode->next = head;
  printf("Pushed %d\n", data);
  return newNode;
}

Node *pop(Node *head) {
  if (!head) {
    printf("Stack is empty!\n");
    return NULL;
  }
  printf("Popped %d\n", head->data);
  Node *temp = head;
  head = head->next;
  free(temp);
  return head;
}

void peek(Node *head) {
  if (!head) {
    printf("Stack is empty!\n");
  } else {
    printf("Top of stack: %d\n", head->data);
  }
}

bool isEmpty(Node *head) { return head == NULL; }
