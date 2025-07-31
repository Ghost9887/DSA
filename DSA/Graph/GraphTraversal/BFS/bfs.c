// W3Schools implementation of BFS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int **adj_matrix;
  char *vertex_data;
  int size;
} Graph;

Graph *create_graph(int size) {
  Graph *g = malloc(sizeof(Graph));
  g->size = size;

  g->adj_matrix = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) {
    g->adj_matrix[i] = calloc(size, sizeof(int));
  }

  g->vertex_data = malloc(size * sizeof(char));
  return g;
}

void add_edge(Graph *g, int u, int v) {
  if (u >= 0 && u < g->size && v >= 0 && v < g->size) {
    g->adj_matrix[u][v] = 1;
    // g->adj_matrix[v][u] = 1;
  }
}

void add_vertex_data(Graph *g, int vertex, char data) {
  if (vertex >= 0 && vertex < g->size) {
    g->vertex_data[vertex] = data;
  }
}

void print_graph(Graph *g) {
  printf("Adjacency Matrix:\n");
  for (int i = 0; i < g->size; i++) {
    for (int j = 0; j < g->size; j++) {
      printf("%d ", g->adj_matrix[i][j]);
    }
    printf("\n");
  }
  printf("\nVertex Data:\n");
  for (int i = 0; i < g->size; i++) {
    printf("Vertex %d: %c\n", i, g->vertex_data[i]);
  }
}

// Breadth-First Search
void bfs(Graph *g, char start_vertex_data) {
  bool *visited = calloc(g->size, sizeof(bool));
  int *queue = malloc(g->size * sizeof(int));
  int front = 0, rear = 0;
  int start_vertex = -1;

  for (int i = 0; i < g->size; i++) {
    if (g->vertex_data[i] == start_vertex_data) {
      start_vertex = i;
      break;
    }
  }

  if (start_vertex != -1) {
    queue[rear++] = start_vertex;
    visited[start_vertex] = true;

    while (front < rear) {
      int current_vertex = queue[front++];
      printf("%c ", g->vertex_data[current_vertex]);

      for (int i = 0; i < g->size; i++) {
        if (g->adj_matrix[current_vertex][i] == 1 && !visited[i]) {
          queue[rear++] = i;
          visited[i] = true;
        }
      }
    }
  }
  free(queue);
  free(visited);
}

void free_graph(Graph *g) {
  for (int i = 0; i < g->size; i++) {
    free(g->adj_matrix[i]);
  }
  free(g->adj_matrix);
  free(g->vertex_data);
  free(g);
}

int main() {
  Graph *g = create_graph(7);

  add_vertex_data(g, 0, 'A');
  add_vertex_data(g, 1, 'B');
  add_vertex_data(g, 2, 'C');
  add_vertex_data(g, 3, 'D');
  add_vertex_data(g, 4, 'E');
  add_vertex_data(g, 5, 'F');
  add_vertex_data(g, 6, 'G');

  add_edge(g, 3, 0); // D -> A
  add_edge(g, 3, 4); // D -> E
  add_edge(g, 4, 0); // E -> A
  add_edge(g, 0, 2); // A -> C
  add_edge(g, 2, 5); // C -> F
  add_edge(g, 2, 6); // C -> G
  add_edge(g, 5, 1); // F -> B
  add_edge(g, 1, 2); // B -> C

  print_graph(g);

  printf("\n\nBreadth First Search starting from vertex D:\n");
  bfs(g, 'D');

  free_graph(g);
  return 0;
}
