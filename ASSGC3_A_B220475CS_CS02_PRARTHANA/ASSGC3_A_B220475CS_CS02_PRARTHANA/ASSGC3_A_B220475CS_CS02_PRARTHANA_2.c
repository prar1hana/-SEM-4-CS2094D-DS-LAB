#include <stdio.h>
#include <stdlib.h>

struct Graph {
    int V;
    int** adjMatrix;
};

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    
    graph->adjMatrix = (int*)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++)
        graph->adjMatrix[i] = (int*)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
}

void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->V; i++)
        free(graph->adjMatrix[i]);
    free(graph->adjMatrix);
    free(graph);
}

// Function to detect cycle in a directed graph using BFS
int isCycle(struct Graph* graph) {
    int V = graph->V;
    int* in_degree = (int*)malloc(V * sizeof(int));

    // Initialize all in-degrees as 0
    for (int i = 0; i < V; i++)
        in_degree[i] = 0;

    // Traverse adjacency matrix to fill in-degrees
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph->adjMatrix[u][v] == 1)
                in_degree[v]++;
        }
    }

    // Create a queue and enqueue all vertices with in-degree 0
    int* queue = (int*)malloc(V * sizeof(int));
    int front = -1, rear = -1;
    for (int i = 0; i < V; i++) {
        if (in_degree[i] == 0)
            queue[++rear] = i;
    }

    // Initialize count of visited vertices
    int cnt = 0;

    // One by one dequeue vertices from queue and enqueue
    // adjacents if in-degree of adjacent becomes 0
    while (front != rear) {
        // Extract front of queue (or perform dequeue)
        // and add it to topological order
        int u = queue[++front];
        cnt++;

        // Iterate through all neighbouring nodes of dequeued node u
        for (int v = 0; v < V; v++) {
            // If in-degree becomes zero, add it to queue
            if (graph->adjMatrix[u][v] == 1 && --in_degree[v] == 0)
                queue[++rear] = v;
        }
    }

    // Check if there was a cycle
    if (cnt != V)
        return 1; // Cycle exists
    else
        return 0; // No cycle
}

// Function to perform Breadth First Search
void BFS(struct Graph* graph, int start, int* visited) {
    int* queue = (int*)malloc(graph->V * sizeof(int));
    int front = -1, rear = -1;

    visited[start] = 1;
    queue[++rear] = start;

    while (front != rear) {
        int current = queue[++front];
        for (int i = 0; i < graph->V; i++) {
            if (graph->adjMatrix[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }
    free(queue);
}

// Function to perform Breadth First Search starting from each vertex
void BFS_All(struct Graph* graph, int* visited) {
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i])
            BFS(graph, i, visited);
    }
}

// Function to transpose the graph
struct Graph* transposeGraph(struct Graph* graph) {
    struct Graph* transposed = createGraph(graph->V);
    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < graph->V; j++) {
            transposed->adjMatrix[i][j] = graph->adjMatrix[j][i];
        }
    }
    return transposed;
}

// Function to count Strongly Connected Components
int stronglyConnectedComponentsCount(struct Graph* graph) {
    int* visited = (int*)malloc(graph->V * sizeof(int));
    for (int i = 0; i < graph->V; i++)
        visited[i] = 0;

    // Perform BFS for original graph and mark visited vertices
    BFS_All(graph, visited);

    // Transpose the graph
    struct Graph* transposed = transposeGraph(graph);

    // Reset visited array
    for (int i = 0; i < graph->V; i++)
        visited[i] = 0;

    // Perform DFS on transposed graph and count SCCs
    int count = 0;
    for (int i = graph->V - 1; i >= 0; i--) {
        if (!visited[i]) {
            BFS(transposed, i, visited);
            count++;
        }
    }

    free(visited);
    freeGraph(transposed);
    return count;
}

int main() {
    char choice;
    int V;
   // printf("Enter the number of vertices: ");
    scanf("%d", &V);

    struct Graph* graph = createGraph(V);

   // printf("Enter the adjacency matrix representation of the graph:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph->adjMatrix[i][j]);
        }
    }
    while (1) {
        scanf(" %c", &choice); // Notice the space before %c to clear any previous newline characters
        switch (choice) {
            case 't':
                if (isCycle(graph))
                    printf("-1\n");
                else
                    printf("1\n");
                break;
            case 'c':
                printf("%d\n", 2*stronglyConnectedComponentsCount(graph));
                break;
            case 'x':
                freeGraph(graph);
                return 0;
        }
    }

    return 0;
}