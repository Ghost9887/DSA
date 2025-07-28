#include <stdio.h>
#include <stdlib.h>

// define a struct for a singly-linked node
typedef struct Node {
  int data;
  struct Node *next;
} Node;

void addNode(Node **head, int data);
void deleteLastNode(Node **head);
void printList(Node *head);
Node *searchList(Node *head, int target);
void updateList(Node *head, int data, int newData);
int getSizeOfList(Node *head);
void reverseList(Node **head);
void freeList(Node **head);

int main() {

  // doesnt point to anything
  Node *head = NULL;
  printf("Adding 5 nodes...\n");
  for (int i = 1; i <= 5; i++) {
    addNode(&head, i);
  }
  printList(head);
  printf("Reversing list....\n");
  reverseList(&head);
  printList(head);
  printf("Searching for data...");
  searchList(head, 3);
  printf("Updating data...");
  updateList(head, 3, 10);
  printf("Size of list: %d\n", getSizeOfList(head));
  printf("Deleting 5 nodes\n");
  for (int i = 1; i <= 5; i++) {
    deleteLastNode(&head);
  }
  printList(head);
  printf("Size of list: %d\n", getSizeOfList(head));
  freeList(&head);

  return 0;
}

// **node is a pointer to a pointer since the original pointer
// doesn't point to anything we have to realocate the pointer
void addNode(Node **head, int data) {

  // make space for a new node!
  Node *newNode = malloc(sizeof(Node));

  newNode->data = data;
  newNode->next = NULL;

  if (*head == NULL) {
    *head = newNode;
    return;
  }

  Node *current = *head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = newNode;
}

void deleteLastNode(Node **head) {

  Node *current = *head;

  // if the list is empty don't do anything
  if (current == NULL) {
    return;
  }

  else if (current->next == NULL) {
    free(current);
    *head = NULL;
    return;
  }

  while (current->next->next != NULL) {
    current = current->next;
  }

  free(current->next);
  current->next = NULL;
}

Node *searchList(Node *head, int target) {
  if (head == NULL) {
    printf("List is empty\n");
    return NULL;
  }

  int i = -1;
  while (head != NULL) {
    i++;
    if (head->data == target) {
      break;
    }
    head = head->next;
  }

  if (i != -1) {
    printf("Index: %d\n", i);
  } else {
    return NULL;
  }
  return head;
}

void updateList(Node *head, int data, int newData) {

  head = searchList(head, data);
  if (head == NULL) {
    printf("Target data not found\n");
    return;
  }
  head->data = newData;
  printf("New Data %d\n", head->data);
}

int getSizeOfList(Node *head) {
  if (head == NULL) {
    return -1;
  }

  int count = 0;
  while (head != NULL) {
    count++;
    head = head->next;
  }
  return count;
}

void reverseList(Node **head) {

  if (*head == NULL) {
    printf("List is empty\n");
  }

  Node *prev = NULL;
  Node *current = *head;

  // flipping the arrows in the other direction basically
  while (current != NULL) {
    Node *next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  *head = prev;
}

void printList(Node *head) {

  if (head == NULL) {
    printf("List is empty\n");
    return;
  }

  while (head != NULL) {
    printf("%d\n", head->data);
    head = head->next;
  }
}

void freeList(Node **head) {
  Node *current = *head;
  while (current != NULL) {
    Node *temp = current;
    current = current->next;
    free(temp);
  }
  *head = NULL;
}
