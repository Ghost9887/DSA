#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  int level;
  struct Node *rNode;
  struct Node *lNode;
} Node;

void addNode(Node **root, int data);
void printTree(Node *root);
void preOrderTraversal(Node *root);
// finsih implementing
void deleteNode(Node **root, int data);
void deleteRightMostNode(Node *root);
void deleteLeftMostNode(Node *root);
Node *getRightMostNode(Node *root);
Node *getLeftMostNode(Node *root);
Node *searchNode(Node *root, int data);

int main() {

  Node *root = NULL;
  addNode(&root, 10);
  addNode(&root, 8);
  addNode(&root, 9);
  addNode(&root, 12);
  addNode(&root, 11);
  addNode(&root, 4);
  addNode(&root, 15);
  addNode(&root, 14);
  addNode(&root, 13);
  addNode(&root, 7);
  printTree(root);

  return 0;
}

void addNode(Node **root, int data) {

  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->rNode = NULL;
  newNode->lNode = NULL;
  newNode->level = 0;

  if (*root == NULL) {
    *root = newNode;
    return;
  }

  // find where to place the Node
  Node *current = *root;
  bool foundSpot = false;
  while (!foundSpot) {

    if (data < current->data && current->lNode == NULL) {
      newNode->level = current->level + 1;
      current->lNode = newNode;
      foundSpot = true;
      break;
    }

    else if (data > current->data && current->rNode == NULL) {
      newNode->level = current->level + 1;
      current->rNode = newNode;
      foundSpot = true;
      break;
    }

    else if (data < current->data) {
      current = current->lNode;
    }

    else {
      current = current->rNode;
    }
  }
}

void printTree(Node *root) { preOrderTraversal(root); }

void preOrderTraversal(Node *root) {
  if (root == NULL) {
    return;
  }
  printf("Data: %d\n", root->data);
  preOrderTraversal(root->lNode);
  preOrderTraversal(root->rNode);
}
