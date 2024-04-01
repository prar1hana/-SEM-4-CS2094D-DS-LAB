#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000

int adj[MAX_NODES][MAX_NODES];
int visited[MAX_NODES];
int component_sizes[MAX_NODES];
int num_nodes;
int num_components;
int time;
int discovery_time[MAX_NODES];
int lowest_time[MAX_NODES];
int is_articulation_point[MAX_NODES];

int min(int a, int b) {
    return a < b ? a : b;
}

void dfs(int node, int parent) {
    visited[node] = 1;
    discovery_time[node] = lowest_time[node] = ++time;
    int child_count = 0;
    for (int i = 0; i < num_nodes; ++i) {
        if (adj[node][i]) {
            if (!visited[i]) {
                ++child_count;
                dfs(i, node);
                lowest_time[node] = min(lowest_time[node], lowest_time[i]);
                if (lowest_time[i] >= discovery_time[node] && parent != -1)
                    is_articulation_point[node] = 1;
            } else if (i != parent) {
                lowest_time[node] = min(lowest_time[node], discovery_time[i]);
            }
        }
    }
    if (parent == -1 && child_count > 1)
        is_articulation_point[node] = 1;
}

void dfs_bridge(int node, int parent) {
    visited[node] = 1;
    for (int i = 0; i < num_nodes; ++i) {
        if (adj[node][i]) {
            if (!visited[i]) {
                dfs_bridge(i, node);
            } else if (i != parent && discovery_time[i] < discovery_time[node]) {
                lowest_time[node] = min(lowest_time[node], discovery_time[i]);
            }
        }
    }
}

int find_bridges() {
    int bridge_count = 0;
    for (int i = 0; i < num_nodes; ++i) {
        if (!visited[i]) {
            dfs_bridge(i, -1);
        }
        for (int j = 0; j < num_nodes; ++j) {
            if (adj[i][j] && lowest_time[j] > discovery_time[i]) {
                ++bridge_count;
            }
        }
    }
    return bridge_count;
}

void dfs_components(int node) {
    visited[node] = 1;
    ++component_sizes[num_components];
    for (int i = 0; i < num_nodes; ++i) {
        if (adj[node][i] && !visited[i]) {
            dfs_components(i);
        }
    }
}

int find_components() {
    int max_size = 0;
    for (int i = 0; i < num_nodes; ++i) {
        if (!visited[i]) {
            ++num_components;
            dfs_components(i);
            max_size = component_sizes[num_components - 1];
        }
    }
    return max_size;
}

void initialize() {
    for (int i = 0; i < MAX_NODES; ++i) {
        for (int j = 0; j < MAX_NODES; ++j) {
            adj[i][j] = 0;
        }
    }
}

int main() {
    char choice;
    initialize();
    scanf("%d", &num_nodes);
    if (num_nodes > MAX_NODES) {
        printf("Error: Number of nodes exceeds maximum allowed.\n");
        return 1;
    }
    for (int i = 0; i < num_nodes; ++i) {
        int node, num_neighbors;
        scanf("%d %d", &node, &num_neighbors);
        if (num_neighbors > MAX_NODES) {
            printf("Error: Number of neighbors exceeds maximum allowed.\n");
            return 1;
        }
        for (int j = 0; j < num_neighbors; ++j) {
            int neighbor;
            scanf("%d", &neighbor);
            adj[node][neighbor] = 1;
            adj[neighbor][node] = 1; // undirected graph
        }
    }
    while (1) {
        scanf(" %c", &choice);
        if (choice == 't') {
            break;
        } else if (choice == 'n') {
            num_components = 0;
            int max_size = find_components();
            printf("%d\n", max_size);
        } else if (choice == 's') {
            for (int i = 0; i < MAX_NODES; ++i) {
                component_sizes[i] = 0;
                visited[i] = 0; // Reset visited array
            }
            num_components = 0;
            int max_size = find_components();
            printf("%d\n", num_components);
            for (int i = 0; i < num_components; ++i) {
                printf("%d ", component_sizes[i]);
            }
            printf("\n");
        } else if (choice == 'b') {
            for (int i = 0; i < MAX_NODES; ++i) {
                visited[i] = 0;
                lowest_time[i] = discovery_time[i] = 0;
            }
            int bridges = find_bridges();
            printf("%d\n", bridges);
        } else if (choice == 'a') {
            for (int i = 0; i < MAX_NODES; ++i) {
                visited[i] = 0;
                is_articulation_point[i] = 0;
            }
            num_components = 0;
            int max_size = find_components(); // Re-calculate components
            for (int i = 0; i < num_nodes; ++i) {
                if (!visited[i]) {
                    dfs(i, -1);
                }
            }
            int articulation_points = 0;
            for (int i = 0; i < num_nodes; ++i) {
                if (is_articulation_point[i]) {
                    ++articulation_points;
                }
            }
            printf("%d\n", articulation_points);
        }
    }
    return 0;
}
