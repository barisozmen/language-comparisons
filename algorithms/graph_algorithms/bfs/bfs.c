// Breadth-First Search: Level-by-level exploration
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NODES 100
#define MAX_NEIGHBORS 10
#define MAX_NAME 10

typedef struct {
    char name[MAX_NAME];
    char neighbors[MAX_NEIGHBORS][MAX_NAME];
    int neighbor_count;
} Node;

typedef struct {
    char nodes[MAX_NODES][MAX_NAME];
    int count;
} Path;

typedef struct {
    char node[MAX_NAME];
    Path path;
} QueueItem;


int find_node_index(Node* graph, int graph_size, const char* name) {
    for (int i = 0; i < graph_size; i++) {
        if (strcmp(graph[i].name, name) == 0) return i;
    }
    return -1;
}


bool is_visited(char visited[][MAX_NAME], int visited_count, const char* name) {
    for (int i = 0; i < visited_count; i++) {
        if (strcmp(visited[i], name) == 0) return true;
    }
    return false;
}


Path bfs_iterative(Node* graph, int graph_size, const char* start, const char* goal) {
    Path result = {.count = 0};
    
    if (strcmp(start, goal) == 0) {
        strcpy(result.nodes[0], start);
        result.count = 1;
        return result;
    }
    
    QueueItem queue[MAX_NODES];
    int front = 0, rear = 0;
    char visited[MAX_NODES][MAX_NAME];
    int visited_count = 0;
    
    // Initialize queue
    strcpy(queue[rear].node, start);
    strcpy(queue[rear].path.nodes[0], start);
    queue[rear].path.count = 1;
    rear++;
    
    strcpy(visited[visited_count++], start);
    
    while (front < rear) {
        QueueItem current = queue[front++];
        int node_idx = find_node_index(graph, graph_size, current.node);
        
        if (node_idx == -1) continue;
        
        for (int i = 0; i < graph[node_idx].neighbor_count; i++) {
            const char* neighbor = graph[node_idx].neighbors[i];
            
            if (is_visited(visited, visited_count, neighbor)) continue;
            
            if (strcmp(neighbor, goal) == 0) {
                for (int j = 0; j < current.path.count; j++) {
                    strcpy(result.nodes[j], current.path.nodes[j]);
                }
                strcpy(result.nodes[current.path.count], neighbor);
                result.count = current.path.count + 1;
                return result;
            }
            
            strcpy(visited[visited_count++], neighbor);
            
            strcpy(queue[rear].node, neighbor);
            for (int j = 0; j < current.path.count; j++) {
                strcpy(queue[rear].path.nodes[j], current.path.nodes[j]);
            }
            strcpy(queue[rear].path.nodes[current.path.count], neighbor);
            queue[rear].path.count = current.path.count + 1;
            rear++;
        }
    }
    
    return result;
}


int main() {
    Node graph[] = {
        {"A", {"B", "C"}, 2},
        {"B", {"D", "E"}, 2},
        {"C", {"F"}, 1},
        {"D", {}, 0},
        {"E", {"F"}, 1},
        {"F", {}, 0}
    };
    int graph_size = 6;
    
    Path path = bfs_iterative(graph, graph_size, "A", "F");
    
    printf("Path: ");
    for (int i = 0; i < path.count; i++) {
        printf("%s ", path.nodes[i]);
    }
    printf("\n");
    
    return 0;
}

