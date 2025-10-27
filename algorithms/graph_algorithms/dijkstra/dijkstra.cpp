// Dijkstra's Algorithm: Shortest path in weighted graphs
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

struct State {
    int cost;
    string node;
    vector<string> path;
    
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};


pair<vector<string>, int> dijkstra_heap(
    const unordered_map<string, vector<pair<string, int>>>& graph,
    const string& start, const string& goal) {
    
    priority_queue<State, vector<State>, greater<State>> pq;
    unordered_set<string> visited;
    
    pq.push({0, start, {start}});
    
    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();
        
        if (visited.count(current.node)) continue;
        if (current.node == goal) {
            return {current.path, current.cost};
        }
        
        visited.insert(current.node);
        
        auto it = graph.find(current.node);
        if (it != graph.end()) {
            for (const auto& [neighbor, weight] : it->second) {
                if (!visited.count(neighbor)) {
                    auto new_path = current.path;
                    new_path.push_back(neighbor);
                    pq.push({current.cost + weight, neighbor, new_path});
                }
            }
        }
    }
    
    return {{}, numeric_limits<int>::max()};
}


pair<vector<string>, int> dijkstra_array(
    const unordered_map<string, vector<pair<string, int>>>& graph,
    const string& start, const string& goal) {
    
    unordered_map<string, int> distances;
    unordered_map<string, string> previous;
    unordered_set<string> unvisited;
    
    for (const auto& [node, _] : graph) {
        distances[node] = numeric_limits<int>::max();
        unvisited.insert(node);
    }
    distances[start] = 0;
    
    while (!unvisited.empty()) {
        string current;
        int min_dist = numeric_limits<int>::max();
        
        for (const auto& node : unvisited) {
            if (distances[node] < min_dist) {
                min_dist = distances[node];
                current = node;
            }
        }
        
        if (min_dist == numeric_limits<int>::max()) break;
        
        if (current == goal) {
            vector<string> path;
            string node = current;
            while (!node.empty()) {
                path.insert(path.begin(), node);
                node = previous[node];
            }
            return {path, distances[goal]};
        }
        
        unvisited.erase(current);
        
        auto it = graph.find(current);
        if (it != graph.end()) {
            for (const auto& [neighbor, weight] : it->second) {
                int new_dist = distances[current] + weight;
                if (new_dist < distances[neighbor]) {
                    distances[neighbor] = new_dist;
                    previous[neighbor] = current;
                }
            }
        }
    }
    
    return {{}, numeric_limits<int>::max()};
}


int main() {
    unordered_map<string, vector<pair<string, int>>> graph = {
        {"A", {{"B", 1}, {"C", 4}}},
        {"B", {{"C", 2}, {"D", 5}}},
        {"C", {{"D", 1}}},
        {"D", {}}
    };
    
    auto [path, cost] = dijkstra_heap(graph, "A", "D");
    for (const auto& node : path) cout << node << " ";
    cout << "with cost " << cost << endl;
    
    return 0;
}

