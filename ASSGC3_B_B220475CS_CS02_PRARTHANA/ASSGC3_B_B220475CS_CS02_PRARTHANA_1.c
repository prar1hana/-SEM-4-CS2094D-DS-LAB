////////////////////////q1///////////////////////
/////////////////////made by prarthana///////////
////////////////////b220475cs////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

int V;

int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}


void primMST(int** graph, int s, int** mst) {
    int parent[V];
    int key[V];
    bool mstSet[V];
    
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
        
 
    key[s] = 0;
    parent[s] = -1; 
    
    // Initialize variables to store the cheapest discovered edge
    int cheapest_u = -1, cheapest_v = -1, cheapest_weight = INT_MAX;

    int count = 0; // To keep track of the edges added to MST

    while (count < V) {
        // Find the cheapest edge not yet in MST
        for (int u = 0; u < V; u++) {
            if (mstSet[u] == false && key[u] < cheapest_weight) {
                cheapest_weight = key[u];
                cheapest_u = u;
                cheapest_v = parent[u];
            }
        }

        // Add the cheapest discovered edge to MST
        mstSet[cheapest_u] = true;
        mst[count][0] = cheapest_v;
        mst[count][1] = cheapest_u;
        count++;

        // Update key values and parent vertices
        for (int v = 0; v < V; v++) {
            if (graph[cheapest_u][v] && mstSet[v] == false && graph[cheapest_u][v] < key[v]) {
                parent[v] = cheapest_u;
                key[v] = graph[cheapest_u][v];
            }
        }

        // Reset variables for the next iteration
        cheapest_weight = INT_MAX;
    }
    // Don't return mst; just update it.
}

void Sequence(int** graph, int s, int** mst){
    primMST(graph, s, mst);
    for (int i = 1; i < V ; i++) {
        printf("%d %d ", mst[i][0], mst[i][1]);
    }
    printf("\n");
}

void Total_weight(int** graph, int** mst){
    primMST(graph, 0, mst);
    int weight=0;
    for (int i = 1; i < V ; i++){
      weight+=graph[mst[i][0]][ mst[i][1]];
    }
    printf("%d\n", weight);
}

int main() {
    int size;
    
    scanf("%d", &size);
    V = size;
   
    int **graph = (int **)malloc(size * sizeof(int *));
    if(graph == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for(int i = 0; i < size; i++) {
        graph[i] = (int *)malloc(size * sizeof(int));
        if(graph[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            scanf("%d ", &graph[i][j]);
        }
    }
    
    int **mst = (int **)malloc((size ) * sizeof(int *));
    if(mst == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for(int i = 0; i < size; i++) {
        mst[i] = (int *)malloc(2 * sizeof(int));
        if(mst[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }
 
    char str[10];
    while (1) {
        fgets(str, sizeof(str), stdin);
        if(str[0]=='t' && str[1]=='\n'){ 
            Total_weight(graph,mst);
        }
        else if(str[0]=='s' && str[1]=='('){ 
            char *ptr=strchr(str,'(');
            ptr++;
            int x=atoi(ptr);
            Sequence(graph, x, mst);
        }
        else if(str[0]=='x'&&str[1]=='\n'){ 
            break;
        }
        else{
            printf("invalid input\n");
        }
    }
    
    for(int i = 0; i < size; i++) {
        free(graph[i]);
    }
    free(graph);
    for(int i = 0; i < size - 1; i++) {
      free(mst[i]);
    }
    free(mst);
    return 0;
}

