#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// Structure to represent a node in the adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Structure to represent the adjacency list
typedef struct Graph {
    Node* adjList[MAX_NODES];
    int numNodes;
} Graph;

// Function to initialize a graph
Graph* initializeGraph(int numNodes) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    graph->numNodes = numNodes;

    for (int i = 0; i < numNodes; ++i) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// Function to print all paths from src to dest
void printAllPathsUtil(Graph* graph, int src, int dest, int* visited, int* path, int pathLen) {
    visited[src] = 1;
    path[pathLen++] = src;

    if (src == dest) {
        for (int i = 0; i < pathLen; ++i) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        Node* temp = graph->adjList[src];
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                printAllPathsUtil(graph, temp->vertex, dest, visited, path, pathLen);
            }
            temp = temp->next;
        }
    }

    visited[src] = 0;
}

// Function to print all paths from src to dest
void printAllPaths(Graph* graph, int src, int dest) {
    int* visited = (int*)calloc(graph->numNodes, sizeof(int));
    int* path = (int*)malloc(graph->numNodes * sizeof(int));
    int pathLen = 0;

    //printf("Paths from %d to %d:\n", src, dest);
    printAllPathsUtil(graph, src, dest, visited, path, pathLen);

    free(visited);
    free(path);
}
// Function to check if the graph has a cycle using DFS
int hasCycle(Graph* graph, int v, int parent, int* visited) {
    visited[v] = 1;

    Node* temp = graph->adjList[v];
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            if (hasCycle(graph, adjVertex, v, visited)) {
                return 1;
            }
        } else if (adjVertex != parent) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
// Function to check if the graph is a valid tree
int CheckValidTree(Graph* graph) {
    int* visited = (int*)calloc(graph->numNodes, sizeof(int));

    // Check for cycle
    if (hasCycle(graph, 0, -1, visited)) {
        free(visited);
        return 0;
    }

    // Check if all vertices are reachable from the root
    for (int i = 0; i < graph->numNodes; ++i) {
        if (!visited[i]) {
            free(visited);
            return 0;
        }
    }

    // Check for isolated vertices
    for (int i = 0; i < graph->numNodes; ++i) {
        if (graph->adjList[i] == NULL) {
            free(visited);
            return 0;
        }
    }

    free(visited);
    return 1;
}



int main() {
    char choice;
    int N;
    //printf("Enter the number of nodes: ");
    scanf("%d", &N);

    Graph* graph = initializeGraph(N);

   // Input the adjacency list
for (int i = 0; i < N; ++i) {
    int node, adjNode;
   // printf("Enter node %d and its adjacent nodes separated by space (press Enter to finish): ", i + 1);
    scanf("%d", &node);
    while (1) {
        scanf("%d", &adjNode);
        addEdge(graph, node, adjNode);
        char ch = getchar(); // read the next character
        if (ch == '\n' || ch == EOF) // break if newline or end of file is encountered
            break;
    }
}


    while (1) {
       // printf("Enter 'a' followed by node1 and node2 to print paths or 't' to check if the graph is a valid tree: ");
        scanf(" %c", &choice);

        if (choice == 'x') {
            break;
        } else if (choice == 'a') {
            int node1, node2;
            scanf("%d %d", &node1, &node2);
            printAllPaths(graph, node1, node2);
        } else if (choice == 't') {
            if (CheckValidTree(graph)) {
                printf("1\n");
            } else {
                printf("-1\n");
            }
        }
    }

    // Free allocated memory
    for (int i = 0; i < N; ++i) {
        Node* temp = graph->adjList[i];
        while (temp != NULL) {
            Node* prev = temp;
            temp = temp->next;
            free(prev);
        }
    }
    free(graph);

    return 0;
}