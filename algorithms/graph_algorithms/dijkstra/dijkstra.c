// Dijkstra's Algorithm: Shortest path in weighted graphs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_NODES 100
#define MAX_NEIGHBORS 10
#define MAX_NAME 10
#define INF INT_MAX

typedef struct {
    char name[MAX_NAME];
    int weight;
} Edge;

typedef struct {
    char name[MAX_NAME];
    Edge edges[MAX_NEIGHBORS];
    int edge_count;
} Node;

typedef struct {
    char nodes[MAX_NODES][MAX_NAME];
    int count;
} Path;


int find_node_index(Node* graph, int graph_size, const char* name) {
    for (int i = 0; i < graph_size; i++) {
        if (strcmp(graph[i].name, name) == 0) return i;
    }
    return -1;
}


int dijkstra_array(Node* graph, int graph_size, const char* start, const char* goal, Path* result) {
    int distances[MAX_NODES];
    int previous[MAX_NODES];
    bool visited[MAX_NODES];
    
    for (int i = 0; i < graph_size; i++) {
        distances[i] = INF;
        previous[i] = -1;
        visited[i] = false;
    }
    
    int start_idx = find_node_index(graph, graph_size, start);
    int goal_idx = find_node_index(graph, graph_size, goal);
    
    if (start_idx == -1 || goal_idx == -1) return INF;
    
    distances[start_idx] = 0;
    
    for (int count = 0; count < graph_size; count++) {
        int min_dist = INF;
        int current = -1;
        
        for (int i = 0; i < graph_size; i++) {
            if (!visited[i] && distances[i] < min_dist) {
                min_dist = distances[i];
                current = i;
            }
        }
        
        if (current == -1 || min_dist == INF) break;
        
        if (current == goal_idx) {
            // Reconstruct path
            int path_indices[MAX_NODES];
            int path_len = 0;
            int idx = goal_idx;
            
            while (idx != -1) {
                path_indices[path_len++] = idx;
                idx = previous[idx];
            }
            
            for (int i = path_len - 1; i >= 0; i--) {
                strcpy(result->nodes[result->count++], graph[path_indices[i]].name);
            }
            
            return distances[goal_idx];
        }
        
        visited[current] = true;
        
        for (int i = 0; i < graph[current].edge_count; i++) {
            const char* neighbor_name = graph[current].edges[i].name;
            int weight = graph[current].edges[i].weight;
            int neighbor_idx = find_node_index(graph, graph_size, neighbor_name);
            
            if (neighbor_idx != -1 && !visited[neighbor_idx]) {
                int new_dist = distances[current] + weight;
                if (new_dist < distances[neighbor_idx]) {
                    distances[neighbor_idx] = new_dist;
                    previous[neighbor_idx] = current;
                }
            }
        }
    }
    
    return INF;
}


int main() {
    Node graph[] = {
        {"A", {{"B", 1}, {"C", 4}}, 2},
        {"B", {{"C", 2}, {"D", 5}}, 2},
        {"C", {{"D", 1}}, 1},
        {"D", {}, 0}
    };
    int graph_size = 4;
    
    Path path = {.count = 0};
    int cost = dijkstra_array(graph, graph_size, "A", "D", &path);
    
    printf("Path: ");
    for (int i = 0; i < path.count; i++) {
        printf("%s ", path.nodes[i]);
    }
    printf("with cost %d\n", cost);
    
    return 0;
}

