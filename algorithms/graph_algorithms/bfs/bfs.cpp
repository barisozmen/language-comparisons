// Breadth-First Search: Level-by-level exploration
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;


vector<string> bfs_iterative(const unordered_map<string, vector<string>>& graph, 
                              const string& start, const string& goal) {
    if (start == goal) return {start};
    
    queue<pair<string, vector<string>>> q;
    unordered_set<string> visited;
    
    q.push({start, {start}});
    visited.insert(start);
    
    while (!q.empty()) {
        auto [node, path] = q.front();
        q.pop();
        
        auto it = graph.find(node);
        if (it != graph.end()) {
            for (const auto& neighbor : it->second) {
                if (visited.count(neighbor)) continue;
                if (neighbor == goal) {
                    path.push_back(neighbor);
                    return path;
                }
                visited.insert(neighbor);
                auto new_path = path;
                new_path.push_back(neighbor);
                q.push({neighbor, new_path});
            }
        }
    }
    
    return {};
}


vector<vector<string>> bfs_level_order(const unordered_map<string, vector<string>>& graph,
                                       const string& start) {
    vector<vector<string>> levels;
    queue<string> q;
    unordered_set<string> visited;
    
    q.push(start);
    visited.insert(start);
    
    while (!q.empty()) {
        int level_size = q.size();
        vector<string> level;
        
        for (int i = 0; i < level_size; i++) {
            string node = q.front();
            q.pop();
            level.push_back(node);
            
            auto it = graph.find(node);
            if (it != graph.end()) {
                for (const auto& neighbor : it->second) {
                    if (!visited.count(neighbor)) {
                        visited.insert(neighbor);
                        q.push(neighbor);
                    }
                }
            }
        }
        levels.push_back(level);
    }
    
    return levels;
}


int main() {
    unordered_map<string, vector<string>> graph = {
        {"A", {"B", "C"}},
        {"B", {"D", "E"}},
        {"C", {"F"}},
        {"D", {}},
        {"E", {"F"}},
        {"F", {}}
    };
    
    auto path = bfs_iterative(graph, "A", "F");
    for (const auto& node : path) cout << node << " ";
    cout << endl;
    
    return 0;
}
