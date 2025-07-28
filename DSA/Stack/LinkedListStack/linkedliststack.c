#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
  int top;
}Stack;

typedef struct Node{
  int data;
  struct Node *next;
}Node;


void push(Node **head, Stack *stack, int data);
void pop(Node **head, Stack *stack);
void peak(Stack *stack);
bool isEmpty(Stack *stack);

int main(){
  Stack stack;
  stack.top = -1;
  Node *head = NULL;

  push(&head, &stack, 1);
  push(&head, &stack, 2);
  push(&head, &stack, 3);
  peak(&stack);
  pop(&head, &stack);
  peak(&stack);
  isEmpty(&stack);
  pop(&head, &stack);
  pop(&head, &stack);

  return 0;
}

void push(Node **head, Stack *stack, int data){
  
  Node *newNode = malloc(sizeof(Node));

  newNode->data = data;
  newNode->next = NULL;

  if(*head == NULL){
    *head = newNode;
    stack->top = newNode->data;
    printf("Pushed %d to the top of the stack\n", newNode->data);
    return;
  }

  Node *current = *head;
  while(current->next != NULL){
    current = current->next;
  }

  current->next = newNode;
  stack->top = newNode->data;
  printf("Pushed %d to the top of the stack\n", newNode->data);
}

void pop(Node **head, Stack *stack){
  Node *current = *head;

  if(current == NULL){
    printf("List is empty!\n");
    return;
  }

  else if(current->next == NULL){
    free(current);
    *head = NULL;
    stack->top = -1;
    return;
  }
  
  while(current->next->next != NULL){
    current = current->next;
  }
  printf("Popped top: %d\n", current->next->data);
  stack->top = current->data;
  free(current->next);
  current->next = NULL;
}

void peak(Stack *stack){
  printf("Data at top: %d\n", stack->top);
}

bool isEmpty(Stack *stack){
  if(stack->top == -1){
    return true;
  }
  return false;
}


