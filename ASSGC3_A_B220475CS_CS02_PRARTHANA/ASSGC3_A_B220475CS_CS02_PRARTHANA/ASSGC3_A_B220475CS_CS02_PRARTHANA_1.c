/////////////////QUES1/////////////////////////////////
//////////////////////////////////////////////////////////
//MADE BY PRARTHANA////////B220475CS/////////////////////
////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

typedef struct Node 
{
    int destination;
    struct Node* next;
} Node;

typedef struct Graph 
{
    int V;
    Node** adjList;
} Graph;

typedef struct list 
{
    int v;
    struct list* next;
} List;

List* Make(int k) 
{
    List* x = (List*)malloc(sizeof(List));
    x->v = k;
    x->next = NULL;
    return x;
}

Node* MakeNode(int dest) 
{
    Node* newNode= (Node*)malloc(sizeof(Node));
    newNode->destination = dest;
    newNode->next = NULL;
    return newNode;
}

Graph* MakeGraph(int V) {
    Graph* graph =(Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->adjList =(Node**)malloc((V + 1) * sizeof(Node));

    for (int vertex=1; vertex <= V; ++vertex)
        graph->adjList[vertex] = NULL;

    return graph;
}

void AddingEdges(Graph* graph, int src, int dest) {
    Node* newNode = MakeNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}
// Depth First Search (DFS) traversal starting from vertex v.
void DepthFirstSearchUtilityfunction(int v, Graph* graph, int isVisited[]) {
    isVisited[v] = 1;
    Node* temp = graph->adjList[v];

    while (temp) {
        int adjVertex = temp->destination;
        if (!isVisited[adjVertex])
            DepthFirstSearchUtilityfunction(adjVertex, graph, isVisited);
        temp = temp->next;
    }
}

int ConnectedComponentsNumber(Graph* graph) {
    int V = graph->V;
    int* isVisited = (int*)malloc((V + 1) * sizeof(int));
    int count = 0;

    for (int vertex = 1; vertex <= V; ++vertex)
        isVisited[vertex] = 0;

    for (int vertex = 1; vertex <= V; ++vertex) {
        if (!isVisited[vertex]) {
            DepthFirstSearchUtilityfunction(vertex, graph, isVisited);
            ++count;
        }
    }

    free(isVisited);
    return count;
}
// (dfs traversal to calc the size of each connected component)
void DepthFirstSearchUtilityfunction2(int v, Graph* graph, int isVisited[], int* count) {
    isVisited[v] = 1;
    Node* temp = graph->adjList[v];

    while (temp) {
        int adjVertex = temp->destination;
        if (!isVisited[adjVertex]) {
            (*count)++;
            DepthFirstSearchUtilityfunction2(adjVertex, graph, isVisited, count);
        }
        temp = temp->next;
    }
}

void SIZE(Graph* graph) {
    int V = graph->V;
    int* isVisited = (int*)malloc((V + 1) * sizeof(int));
    List* li = NULL;

    for (int vertex = 1; vertex <= V; ++vertex)
        isVisited[vertex] = 0;

    for (int vertex = 1; vertex <= V; ++vertex) {
        if (!isVisited[vertex]) {
            int count = 0;
            DepthFirstSearchUtilityfunction2(vertex, graph, isVisited, &count);
            List* x = Make(count + 1);
            List* prev = NULL;
            List* curr = li;

            while (curr && curr->v <= x->v) {
                prev = curr;
                curr = curr->next;
            }

            if (prev == NULL) {
                x->next = li;
                li = x;
            } else {
                prev->next = x;
                x->next = curr;
            }
        }
    }
    List* cu = li;
    while (cu) {
        printf("%d ", cu->v);
        cu = cu->next;
    }
    printf("\n");
    free(isVisited);
}
//performs DFS traversal nd cals lowLink nd timeStamp values for each vertex 
//to find bridges in graph.
void dfs3(Graph* graph, int vertex, int* lowLink, int* timeStamp, int* isVisited, int* c, int p, int* time) {
    isVisited[vertex] = 1;
    lowLink[vertex] = *time;
    timeStamp[vertex] = *time;
    (*time)++;
    Node* temp = graph->adjList[vertex];
    while (temp != NULL) {
        if (temp->destination == p) {
            temp = temp->next;
            continue;
        }
        if (!isVisited[temp->destination]) {
            dfs3(graph, temp->destination, lowLink, timeStamp, isVisited, c, vertex, time);
            if (lowLink[vertex] > lowLink[temp->destination])
                lowLink[vertex] = lowLink[temp->destination];
            if (lowLink[temp->destination] > timeStamp[vertex])
                (*c) = (*c) + 1;
        } else {
            if (lowLink[vertex] > lowLink[temp->destination])
                lowLink[vertex] = lowLink[temp->destination];
        }

        temp = temp->next;
    }
}

void NumberOfArticulationPoints(Graph* graph, int vertex, int* lowLink, int* timeStamp, int* isVisited, int* articulationPoints, int p, int* time) {
    int child = 0;
    isVisited[vertex] = 1;
    lowLink[vertex] = *time;
    timeStamp[vertex] = *time;
    (*time)++;
    Node* temp = graph->adjList[vertex];
    while (temp != NULL) {
        if (!isVisited[temp->destination]) {
            child++;
            NumberOfArticulationPoints(graph, temp->destination, lowLink, timeStamp, isVisited, articulationPoints, vertex, time);
            if (lowLink[vertex] > lowLink[temp->destination])
                lowLink[vertex] = lowLink[temp->destination];
            if (lowLink[temp->destination] >= timeStamp[vertex] && p != -1) {
                articulationPoints[vertex] = 1;
            }
        } else if (temp->destination != p) {
            if (lowLink[vertex] > timeStamp[temp->destination])
                lowLink[vertex] = timeStamp[temp->destination];
        }
        temp = temp->next;
    }
    if (child > 1 && p == -1) {
        articulationPoints[vertex] = 1;
    }
}

int main(void) {
    int V, vertex, j, c;
    char s[1000];
    int a[100];
    scanf("%d", &V);
    Graph* graph = MakeGraph(V);
    for (vertex = 0; vertex < V; vertex++) {
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
            AddingEdges(graph, vertex + 1, a[j]);
        }
    }
    char ch;
    while (1) {

        scanf(" %c", &ch);
        if (ch == 'n') {
            printf("%d\n", ConnectedComponentsNumber(graph));
        } else if (ch == 's') {
            SIZE(graph);
        } else if (ch == 'b') {
            int isVisited[100];
            for (vertex = 1; vertex <= V; vertex++) {
                isVisited[vertex] = 0;
            }
            int c = 0;
            int lowLink[V + 1];
            int timeStamp[V + 1];
            int time = 1;
            for (vertex = 1; vertex <= V; vertex++) {
                if (!isVisited[vertex]) {
                    time = 1;
                    dfs3(graph, vertex, lowLink, timeStamp, isVisited, &c, -1, &time);
                }
            }
            (c != 0) ? printf("%d\n", c) : printf("-1\n");
        } else if (ch == 'a') {
            int articulationPoints[V + 1];
            int isVisited[100];
            for (vertex = 1; vertex <= V; vertex++) {
                isVisited[vertex] = 0;
                articulationPoints[vertex] = 0;
            }
            int c = 0;
            int lowLink[V + 1];
            int timeStamp[V + 1];
            int time = 1;
            for (vertex = 1; vertex <= V; vertex++) {
                if (!isVisited[vertex]) {
                    NumberOfArticulationPoints(graph, vertex, lowLink, timeStamp, isVisited, articulationPoints, -1, &time);
                }
            }
            for (vertex = 1; vertex <= V; vertex++) {
                if (articulationPoints[vertex] == 1) {
                    c++;
                }
            }
            (c != 0) ? printf("%d\n", c) : printf("-1\n");
        } else if (ch == 't') {
            exit(0);
        }
    }


    return 1;
}
