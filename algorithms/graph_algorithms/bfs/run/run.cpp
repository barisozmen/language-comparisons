// Compile: g++ -std=c++17 run.cpp -o run_cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Simplified BFS for testing
vector<string> bfs(const unordered_map<string, vector<string>>& graph, 
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

int main() {
    unordered_map<string, vector<string>> graph = {
        {"A", {"B", "C"}},
        {"B", {"D", "E"}},
        {"C", {"F"}},
        {"D", {}},
        {"E", {"F"}},
        {"F", {}}
    };
    
    vector<pair<string, string>> tests = {
        {"A", "F"}, {"A", "D"}, {"A", "E"}, {"B", "F"}
    };
    
    for (const auto& [start, goal] : tests) {
        auto path = bfs(graph, start, goal);
        cout << "BFS " << start << "->" << goal << ": [";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    return 0;
}

