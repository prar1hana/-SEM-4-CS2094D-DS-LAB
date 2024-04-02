/////////////////////////
////////////prarthana//////////////
//////////b220475cs//////////////


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_PATH_LENGTH 100

struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode* head;
};

struct Graph {
    int V;
    struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

void printPath(int path[], int path_index) {
    for (int i = 0; i < path_index; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

void printAllPathsUtil(struct Graph* graph, int u, int d, bool visited[], int path[], int path_index, int* count, bool visited_paths[][MAX_PATH_LENGTH]) {
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    if (u == d) {
        if (!visited_paths[u][path_index - 1]) { // Check if this path has not been visited before
            printPath(path, path_index);
            (*count)++;
            visited_paths[u][path_index - 1] = true; // Marking this path as visited
        }
    } else {
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            if (!visited[pCrawl->dest]) {
                printAllPathsUtil(graph, pCrawl->dest, d, visited, path, path_index, count, visited_paths);
            }
            pCrawl = pCrawl->next;
        }
    }

    visited[u] = false; // Reset visited flag for the current node after all paths from it have been explored
}

void printAllPaths(struct Graph* graph, int s, int d) {
    bool* visited = malloc(graph->V * sizeof(bool));
    bool visited_paths[graph->V][MAX_PATH_LENGTH]; // To keep track of visited paths
    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < MAX_PATH_LENGTH; j++) {
            visited_paths[i][j] = false; // Initialize visited paths array
        }
    }
    int* path = malloc(graph->V * sizeof(int));
    int count = 0;
    printAllPathsUtil(graph, s, d, visited, path, 0, &count, visited_paths);
    if (count == 0) {
        printf("No path found between %d and %d\n", s, d);
    }
    free(visited);
    free(path);
}

bool isCyclicUtil(struct Graph* graph, int v, bool visited[], int parent) {
    visited[v] = true;
    struct AdjListNode* pCrawl = graph->array[v].head;
    while (pCrawl != NULL) {
        int dest = pCrawl->dest;
        if (!visited[dest]) {
            if (isCyclicUtil(graph, dest, visited, v))
                return true;
        } else if (dest != parent)
            return true;
        pCrawl = pCrawl->next;
    }
    return false;
}

bool isCyclic(struct Graph* graph) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; i++)
        visited[i] = false;
    for (int i = 0; i < graph->V; i++)
        if (!visited[i] && isCyclicUtil(graph, i, visited, -1))
            return true;
    return false;
}

void DFSUtil(struct Graph* graph, int v, bool visited[]) {
    visited[v] = true;

    struct AdjListNode* pCrawl = graph->array[v].head;
    while (pCrawl != NULL) {
        int dest = pCrawl->dest;
        if (!visited[dest])
            DFSUtil(graph, dest, visited);
        pCrawl = pCrawl->next;
    }
}

bool isConnected(struct Graph* graph) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; i++)
        visited[i] = false;
    int count = 0;
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            DFSUtil(graph, i, visited);
            count++;
        }
    }
    free(visited);
    return count == 1;
}

bool hasIsolatedVertices(struct Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        if (graph->array[i].head == NULL)
            return true;
    }
    return false;
}

int valid_tree(struct Graph* graph) {
    if (!isCyclic(graph) && isConnected(graph) && !hasIsolatedVertices(graph))
        return -1;
    else
        return 1;
}

int main(void) {
    int V, i, j, c;
    char s[1000];
    int a[100];
    scanf("%d", &V);
    struct Graph* graph = createGraph(V);
    for (i = 0; i < V; i++) {
        scanf(" %[^\n]s", s);
        c = 0;
        j = 0;
        while (s[j] != '\0') {
            int num = 0;
            while (s[j] >= '0' && s[j] <= '9') {
                num = num * 10 + (s[j] - '0');
                j++;
            }
            a[c++] = num;
            if (s[j] == ' ') {
                j++;
            }
        }
        for (j = 1; j < c; j++) {
            addEdge(graph, i, a[j]);
            addEdge(graph, a[j], i); // Adding reverse edges for undirected graph
        }
    }

    int so, d;
    char ch;
    while (1) {
        scanf(" %c", &ch);
        if (ch == 'a') {
            scanf("%d %d", &so, &d);
            printAllPaths(graph, so, d);
        } else if (ch == 't') {
            printf("%d\n", valid_tree(graph));
        } else if (ch == 'x') {
            break;
        }
    }

    // ignore (simply Freeing the allocated memory)
    for (int i = 0; i < graph->V; ++i) {
        struct AdjListNode* current = graph->array[i].head;
        while (current != NULL) {
            struct AdjListNode* next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph->array);
    free(graph);

    return 0;
}
