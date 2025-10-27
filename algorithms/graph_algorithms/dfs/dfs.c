// Depth-First Search: Explore deep before backtracking
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


bool dfs_recursive_helper(Node* graph, int graph_size, const char* node, const char* goal,
                          char visited[][MAX_NAME], int* visited_count, Path* path) {
    if (strcmp(node, goal) == 0) {
        strcpy(path->nodes[path->count++], node);
        return true;
    }

    strcpy(visited[(*visited_count)++], node);
    strcpy(path->nodes[path->count++], node);

    int node_idx = find_node_index(graph, graph_size, node);
    if (node_idx != -1) {
        for (int i = 0; i < graph[node_idx].neighbor_count; i++) {
            const char* neighbor = graph[node_idx].neighbors[i];
            if (!is_visited(visited, *visited_count, neighbor)) {
                if (dfs_recursive_helper(graph, graph_size, neighbor, goal, visited, visited_count, path)) {
                    return true;
                }
            }
        }
    }

    path->count--;
    return false;
}


Path dfs_recursive(Node* graph, int graph_size, const char* start, const char* goal) {
    Path path = {.count = 0};
    char visited[MAX_NODES][MAX_NAME];
    int visited_count = 0;
    
    dfs_recursive_helper(graph, graph_size, start, goal, visited, &visited_count, &path);
    return path;
}


Path dfs_iterative(Node* graph, int graph_size, const char* start, const char* goal) {
    typedef struct {
        char node[MAX_NAME];
        Path path;
    } StackItem;

    StackItem stack[MAX_NODES];
    int top = 0;
    char visited[MAX_NODES][MAX_NAME];
    int visited_count = 0;
    Path result = {.count = 0};

    strcpy(stack[top].node, start);
    strcpy(stack[top].path.nodes[0], start);
    stack[top].path.count = 1;
    top++;

    while (top > 0) {
        StackItem current = stack[--top];

        if (is_visited(visited, visited_count, current.node)) continue;
        if (strcmp(current.node, goal) == 0) return current.path;

        strcpy(visited[visited_count++], current.node);

        int node_idx = find_node_index(graph, graph_size, current.node);
        if (node_idx != -1) {
            for (int i = graph[node_idx].neighbor_count - 1; i >= 0; i--) {
                const char* neighbor = graph[node_idx].neighbors[i];
                if (!is_visited(visited, visited_count, neighbor)) {
                    strcpy(stack[top].node, neighbor);
                    for (int j = 0; j < current.path.count; j++) {
                        strcpy(stack[top].path.nodes[j], current.path.nodes[j]);
                    }
                    strcpy(stack[top].path.nodes[current.path.count], neighbor);
                    stack[top].path.count = current.path.count + 1;
                    top++;
                }
            }
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

    Path path = dfs_recursive(graph, graph_size, "A", "F");
    
    printf("Path: ");
    for (int i = 0; i < path.count; i++) {
        printf("%s ", path.nodes[i]);
    }
    printf("\n");

    return 0;
}

