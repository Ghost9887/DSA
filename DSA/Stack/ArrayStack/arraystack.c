#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 250

typedef struct {
  // array to store the stack data
  int array[MAX_SIZE];
  // index of the top element
  int top;
} Stack;

void push(Stack *stack, int data);
void pop(Stack *stack);
int peak(Stack *stack);
bool isEmpty(Stack *stack);
int size(Stack *stack);
void printStack(Stack *stack);

int main() {

  Stack stack;
  // initiate the stack top to -1 (indicates a empty stack)
  stack.top = -1;

  push(&stack, 5);
  push(&stack, 10);
  push(&stack, 20);
  printStack(&stack);
  printf("Popping from stack:\n");
  pop(&stack);
  printStack(&stack);
  printf("Peaking the stack:\n");
  printf("%d\n", peak(&stack));
  printf("Is Empty:\n");
  printf("%b\n", isEmpty(&stack));
  printf("Size:\n");
  printf("%d\n", size(&stack));
  printf("Pop the rest\n");
  pop(&stack);
  pop(&stack);
  printf("Is Empty:\n");
  printf("%b\n", isEmpty(&stack));
  printf("Size:\n");
  printf("%d\n", size(&stack));
  return 0;
}

void push(Stack *stack, int data) {
  // check if the stack is full
  if (stack->top >= MAX_SIZE) {
    printf("Stack Overflow!\n");
    return;
  }

  // preincrement (increments before using)
  stack->array[++stack->top] = data;
  printf("Pushed %d to the top of the stack\n", data);
}

void pop(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Stack Underflow!\n");
    return;
  }
  int popped = stack->array[stack->top];
  stack->top--;
  printf("Popped %d form the top of the stack\n", popped);
}

int peak(Stack *stack) { return stack->array[stack->top]; }

bool isEmpty(Stack *stack) { return stack->top == -1; }

int size(Stack *stack) {
  // since we start at -1
  return stack->top + 1;
}

void printStack(Stack *stack) {
  for (int i = 0; i < size(stack); i++) {
    printf("%d\n", stack->array[i]);
  }
}
