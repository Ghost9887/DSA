// HahsMap implementation following GeeksforGeeks tutorial

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  char *key;
  char *value;
  struct node *next;
};

void setNode(struct node *node, char *key, char *value) {
  node->key = key;
  node->value = value;
  node->next = NULL;
  return;
};

struct hashMap {
  int numOfElements, capacity;
  struct node **arr;
};

void initializeHashMap(struct hashMap *mp) {
  mp->capacity = 100;
  mp->numOfElements = 0;
  mp->arr = (struct node **)malloc(sizeof(struct node *) * mp->capacity);
  return;
}

int hashFunction(struct hashMap *mp, char *key) {
  int bucketIndex;
  int sum = 0, factor = 31;
  for (int i = 0; i < strlen(key); i++) {
    sum = ((sum % mp->capacity) + (((int)key[i]) * factor) % mp->capacity) %
          mp->capacity;
    factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
  }

  bucketIndex = sum;
  return bucketIndex;
}

void insert(struct hashMap *mp, char *key, char *value) {
  int bucketIndex = hashFunction(mp, key);
  struct node *newNode = (struct node *)malloc(sizeof(struct node));
  setNode(newNode, key, value);
  if (mp->arr[bucketIndex] == NULL) {
    mp->arr[bucketIndex] = newNode;
  } else {
    newNode->next = mp->arr[bucketIndex];
    mp->arr[bucketIndex] = newNode;
  }
  return;
}

void delete(struct hashMap *mp, char *key) {
  int bucketIndex = hashFunction(mp, key);
  struct node *prevNode = NULL;
  struct node *currNode = mp->arr[bucketIndex];
  while (currNode != NULL) {

    if (strcmp(key, currNode->key) == 0) {

      if (currNode == mp->arr[bucketIndex]) {
        mp->arr[bucketIndex] = currNode->next;
      }

      else {
        prevNode->next = currNode->next;
      }
      free(currNode);
      break;
    }
    prevNode = currNode;
    currNode = currNode->next;
  }
  return;
}

char *search(struct hashMap *mp, char *key) {

  int bucketIndex = hashFunction(mp, key);

  struct node *bucketHead = mp->arr[bucketIndex];
  while (bucketHead != NULL) {

    if (bucketHead->key == key) {
      return bucketHead->value;
    }
    bucketHead = bucketHead->next;
  }

  char *errorMssg = (char *)malloc(sizeof(char) * 25);
  errorMssg = "Oops! No data found.\n";
  return errorMssg;
}

int main() {

  struct hashMap *mp = (struct hashMap *)malloc(sizeof(struct hashMap));
  initializeHashMap(mp);

  insert(mp, "Yogaholic", "Anjali");
  insert(mp, "pluto14", "Vartika");
  insert(mp, "elite_Programmer", "Manish");
  insert(mp, "GFG", "GeeksforGeeks");
  insert(mp, "decentBoy", "Mayank");

  printf("%s\n", search(mp, "elite_Programmer"));
  printf("%s\n", search(mp, "Yogaholic"));
  printf("%s\n", search(mp, "pluto14"));
  printf("%s\n", search(mp, "decentBoy"));
  printf("%s\n", search(mp, "GFG"));

  // Key is not inserted
  printf("%s\n", search(mp, "randomKey"));

  printf("\nAfter deletion : \n");

  // Deletion of key
  delete(mp, "decentBoy");
  printf("%s\n", search(mp, "decentBoy"));

  return 0;
}
