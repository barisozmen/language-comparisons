// Compile: gcc run.c -o run_c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 10
#define MAX_NAME 5

typedef struct {
    char name[MAX_NAME];
    char neighbors[MAX_NODES][MAX_NAME];
    int neighbor_count;
} Node;

typedef struct {
    char nodes[MAX_NODES][MAX_NAME];
    int count;
} Path;

int find_node(Node* graph, int size, const char* name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(graph[i].name, name) == 0) return i;
    }
    return -1;
}

Path bfs(Node* graph, int graph_size, const char* start, const char* goal) {
    Path result = {.count = 0};
    if (strcmp(start, goal) == 0) {
        strcpy(result.nodes[0], start);
        result.count = 1;
        return result;
    }
    
    typedef struct { char node[MAX_NAME]; Path path; } QItem;
    QItem queue[100];
    int front = 0, rear = 0;
    char visited[MAX_NODES][MAX_NAME];
    int visited_count = 0;
    
    strcpy(queue[rear].node, start);
    strcpy(queue[rear].path.nodes[0], start);
    queue[rear].path.count = 1;
    rear++;
    strcpy(visited[visited_count++], start);
    
    while (front < rear) {
        QItem current = queue[front++];
        int node_idx = find_node(graph, graph_size, current.node);
        
        if (node_idx != -1) {
            for (int i = 0; i < graph[node_idx].neighbor_count; i++) {
                const char* neighbor = graph[node_idx].neighbors[i];
                int is_visited = 0;
                for (int j = 0; j < visited_count; j++) {
                    if (strcmp(visited[j], neighbor) == 0) { is_visited = 1; break; }
                }
                if (is_visited) continue;
                
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
    int size = 6;
    
    const char* tests[][2] = {{"A", "F"}, {"A", "D"}, {"A", "E"}, {"B", "F"}};
    
    for (int i = 0; i < 4; i++) {
        Path path = bfs(graph, size, tests[i][0], tests[i][1]);
        printf("BFS %s->%s: [", tests[i][0], tests[i][1]);
        for (int j = 0; j < path.count; j++) {
            printf("%s", path.nodes[j]);
            if (j < path.count - 1) printf(", ");
        }
        printf("]\n");
    }
    
    return 0;
}

