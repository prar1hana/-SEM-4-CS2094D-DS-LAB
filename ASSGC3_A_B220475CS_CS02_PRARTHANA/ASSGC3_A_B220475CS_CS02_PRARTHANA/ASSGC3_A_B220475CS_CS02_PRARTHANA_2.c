///////////////////////QUES2////////////////////////////BY PRARTHANA//////////
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};


struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}


int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}


void push(struct Stack* stack, int item) {
    stack->array[++stack->top] = item;
}


int pop(struct Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}


void BFS(int v, int N, int graph[MAX_NODES][MAX_NODES], int visited[MAX_NODES], struct Stack* stack) {
    visited[v] = 1;
    for (int i = 0; i < N; i++) {
        if (graph[v][i] == 1 && !visited[i]) {
            BFS(i, N, graph, visited, stack);
        }
    }
    push(stack, v);
}


void BFS_Transpose(int v, int N, int transposedGraph[MAX_NODES][MAX_NODES], int visited[MAX_NODES]) {
    visited[v] = 1;
    for (int i = 0; i < N; i++) {
        if (transposedGraph[v][i] == 1 && !visited[i]) {
            BFS_Transpose(i, N, transposedGraph, visited);
        }
    }
}


int numberOfStronglyComponents(int N, int graph[MAX_NODES][MAX_NODES]) {
    int visited[MAX_NODES] = {0};
    struct Stack* stack = createStack(N);

    
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            BFS(i, N, graph, visited, stack);
        }
    }

    
    int transposedGraph[MAX_NODES][MAX_NODES];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            transposedGraph[j][i] = graph[i][j];
        }
    }

    
    for (int i = 0; i < N; i++) {
        visited[i] = 0;
    }

    int SCC_count = 0;
    while (!isEmpty(stack)) {
        int v = pop(stack);
        if (!visited[v]) {
            BFS_Transpose(v, N, transposedGraph, visited);
            SCC_count++;
        }
    }

    free(stack->array);
    free(stack);
    return SCC_count;
}
#define MAX_NODES 100

struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isFull(struct Queue* queue) {
    return (queue->size == queue->capacity);
}

int isEmptyq(struct Queue* queue) {
    return (queue->size == 0);
}

void enqueue(struct Queue* queue, int item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(struct Queue* queue) {
    if (isEmptyq(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

int topologicalSort(int N, int graph[MAX_NODES][MAX_NODES]) {
    int inDegree[MAX_NODES] = {0};

    // calculate in-degree for each vertex
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {//nested loop iterates over each adjacent vertex j 
            if (graph[i][j] == 1)
                inDegree[j]++;
        }
    }

    struct Queue* queue = createQueue(N);
    int visitedCount = 0;

    // Enqueue vertices with in-degree 0
    for (int i = 0; i < N; i++) {
        if (inDegree[i] == 0)
            enqueue(queue, i);
    }

    while (!isEmptyq(queue)) {
        int u = dequeue(queue);
        visitedCount++;//This count keeps track of the number of vertices processed during the topological sort.
        for (int v = 0; v < N; v++) {
            if (graph[u][v] == 1) {
                inDegree[v]--;
                if (inDegree[v] == 0)
                    enqueue(queue, v);
            }
        }
    }

    free(queue->array);
    free(queue);

    // If all vertices are visited during the sort, topological sort is possible
    return visitedCount == N;
// } if the number of vertices visited during the topological sort is equal to the total number of vertices in the graph.
// If all vertices are visited during the sort, it means a topological sort is possible, and it returns 1; otherwise, it returns 0.

int main(void) {
  int tps;
    int N;
    scanf("%d", &N);
    int graph[MAX_NODES][MAX_NODES];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    //If all vertices are visited during the sort, it means a topological sort is possible, and it returns 1; otherwise, it returns 0.
    char option;
    do {
        scanf(" %c", &option);
        switch(option) {
            case 't':
            tps=topologicalSort(N, graph);
            if(tps==0)
              tps=-1;
            else
              tps=1;
                printf("%d\n", tps);
                break;
            case 'c':
                 printf("%d\n", numberOfStronglyComponents(N, graph));
                break;
            case 'x':
                break;
            default:
                printf("Invalid option\n");
        }
    } while(option != 'x');
    return 0;
}
