#include <inttypes.h>
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
Node *deleteNode(Node **root, int data);
Node *findMin(Node *node);
void deleteRightMostNode(Node **root);
void deleteLeftMostNode(Node **root);

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
  printf("First print:\n");
  printTree(root);
  printf("-------------------\n");
  printf("Second print: (deleted node 8)\n");
  deleteNode(&root, 8);
  printTree(root);
  printf("-------------------\n");
  printf("Third print: (deleted Right Most Node)\n");
  deleteRightMostNode(&root);
  printTree(root);
  printf("-------------------\n");
  printf("Fourth print: (deleted Left Most Node)\n");
  deleteLeftMostNode(&root);
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

Node *deleteNode(Node **root, int data) {
  if (*root == NULL) {
    printf("Tree is empty!\n");
    return NULL;
  }

  Node *current = *root;

  if (data < current->data) {
    current->lNode = deleteNode(&current->lNode, data);
  } else if (data > current->data) {
    current->rNode = deleteNode(&current->rNode, data);
  } else {
    if (current->lNode == NULL) {
      Node *temp = current->rNode;
      free(current);
      current = NULL;
      return temp;
    } else if (current->rNode == NULL) {
      Node *temp = current->lNode;
      free(current);
      current = NULL;
      return temp;
    }

    Node *successor = findMin(current->rNode);
    current->data = successor->data;
    current->rNode = deleteNode(&current->rNode, successor->data);
  }

  return current;
}

// helper function for the delete node functions
Node *findMin(Node *node) {
  while (node != NULL && node->lNode != NULL) {
    node = node->lNode;
  }
  return node;
}

void deleteRightMostNode(Node **root) {
  if (*root == NULL) {
    printf("Tree is empty\n");
    return;
  }

  Node *current = *root;
  Node *parent = NULL;

  // go to the right most node
  while (current->rNode != NULL) {
    parent = current;
    current = current->rNode;
  }

  if (parent == NULL) {
    *root = current->lNode;
  } else {
    parent->rNode = current->lNode;
  }

  free(current);
  current = NULL;
}

void deleteLeftMostNode(Node **root) {

  if (*root == NULL) {
    printf("Tree is empty\n");
    return;
  }

  Node *current = *root;
  Node *parent = NULL;

  // go to the left most node
  while (current->lNode != NULL) {
    parent = current;
    current = current->lNode;
  }

  if (parent == NULL) {
    *root = current->rNode;
  } else {
    parent->lNode = current->rNode;
  }

  free(current);
  current = NULL;
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
