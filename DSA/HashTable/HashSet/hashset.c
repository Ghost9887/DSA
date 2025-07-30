#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  char *key;
  char *value;
  struct node *next;
};

typedef struct {
  int numOfElements;
  int capacity;
  struct node **array;
} HashSet;

void initializeHashSet(HashSet *hs);
int hashFunction(HashSet *hs, char *key);
void insert(HashSet *hs, char *key, char *value);
void delete(HashSet *hs, char *key);
bool contains(HashSet *hs, char *key);

int main() {
  HashSet *hs = (HashSet *)malloc(sizeof(HashSet));
  initializeHashSet(hs);
  printf("Added Yogaholic -> Anjali\n");
  insert(hs, "Yogaholic", "Anjali");
  printf("Added pluto14 -> Vartika\n");
  insert(hs, "pluto14", "Vartika");
  printf("Added elite_Programmer -> Manish\n");
  insert(hs, "elite_Programmer", "Manish");
  printf("Added GFG -> GeeksforGeeks\n");
  insert(hs, "GFG", "GeeksforGeeks");
  printf("Added decentBoy -> Mayank\n");
  insert(hs, "decentBoy", "Mayank");

  printf("elite_Programmer contains: %b\n", contains(hs, "elite_Programmer"));
  printf("Yogaholic contains: %b\n", contains(hs, "Yogaholic"));
  printf("pluto14 contains: %b\n", contains(hs, "pluto14"));
  printf("decentBoy contains: %b\n", contains(hs, "decentBoy"));
  printf("GFG contains: %b\n", contains(hs, "GFG"));

  printf("randomKey contains: %b\n", contains(hs, "randomKey"));

  printf("\nAfter deletion 'decentBoy': \n");

  delete(hs, "decentBoy");
  printf("decentBoy contains: %b\n", contains(hs, "decentBoy"));

  return 0;
}

void initializeHashSet(HashSet *hs) {
  hs->capacity = 100;
  hs->numOfElements = 0;
  hs->array = (struct node **)malloc(sizeof(struct node *) * hs->capacity);
}

void insert(HashSet *hs, char *key, char *value) {
  int bucketIndex = hashFunction(hs, key);
  struct node *newNode = (struct node *)malloc(sizeof(struct node));
  newNode->key = key;
  newNode->value = value;
  newNode->next = NULL;
  if (hs->array[bucketIndex] == NULL) {
    hs->array[bucketIndex] = newNode;
  } else {
    newNode->next = hs->array[bucketIndex];
    hs->array[bucketIndex] = newNode;
  }
}

void delete(HashSet *hs, char *key) {
  int bucketIndex = hashFunction(hs, key);
  struct node *prev = NULL;
  struct node *current = hs->array[bucketIndex];
  while (current != NULL) {
    if (strcmp(key, current->key) == 0) {
      if (current == hs->array[bucketIndex]) {
        hs->array[bucketIndex] = current->next;
      } else {
        prev->next = current->next;
      }
      free(current);
      break;
    }
    prev = current;
    current = current->next;
  }
}

bool contains(HashSet *hs, char *key) {
  int bucketIndex = hashFunction(hs, key);
  struct node *bucketHead = hs->array[bucketIndex];
  while (bucketHead != NULL) {
    if (bucketHead->key == key) {
      return true;
    }
    bucketHead = bucketHead->next;
  }
  return false;
}

int hashFunction(HashSet *hs, char *key) {
  int bucketIndex;
  int sum = 0, factor = 31;
  for (int i = 0; i < strlen(key); i++) {
    sum = ((sum % hs->capacity) + (((int)key[i]) * factor) % hs->capacity) %
          hs->capacity;
    factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
  }

  bucketIndex = sum;
  return bucketIndex;
}
