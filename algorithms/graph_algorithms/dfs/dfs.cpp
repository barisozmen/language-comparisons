// Depth-First Search: Explore deep before backtracking
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;


bool dfs_recursive_helper(const unordered_map<string, vector<string>>& graph,
                          const string& node, const string& goal,
                          unordered_set<string>& visited,
                          vector<string>& path) {
    if (node == goal) {
        path.push_back(node);
        return true;
    }

    visited.insert(node);
    path.push_back(node);

    auto it = graph.find(node);
    if (it != graph.end()) {
        for (const auto& neighbor : it->second) {
            if (!visited.count(neighbor)) {
                if (dfs_recursive_helper(graph, neighbor, goal, visited, path)) {
                    return true;
                }
            }
        }
    }

    path.pop_back();
    return false;
}


vector<string> dfs_recursive(const unordered_map<string, vector<string>>& graph,
                             const string& start, const string& goal) {
    unordered_set<string> visited;
    vector<string> path;
    dfs_recursive_helper(graph, start, goal, visited, path);
    return path;
}


vector<string> dfs_iterative(const unordered_map<string, vector<string>>& graph,
                             const string& start, const string& goal) {
    stack<pair<string, vector<string>>> st;
    unordered_set<string> visited;

    st.push({start, {start}});

    while (!st.empty()) {
        auto [node, path] = st.top();
        st.pop();

        if (visited.count(node)) continue;
        if (node == goal) return path;

        visited.insert(node);

        auto it = graph.find(node);
        if (it != graph.end()) {
            for (auto neighbor = it->second.rbegin(); neighbor != it->second.rend(); ++neighbor) {
                if (!visited.count(*neighbor)) {
                    auto new_path = path;
                    new_path.push_back(*neighbor);
                    st.push({*neighbor, new_path});
                }
            }
        }
    }

    return {};
}


vector<string> dfs_postorder(const unordered_map<string, vector<string>>& graph,
                             const string& start,
                             unordered_set<string>& visited) {
    if (visited.count(start)) return {};

    visited.insert(start);
    vector<string> result;

    auto it = graph.find(start);
    if (it != graph.end()) {
        for (const auto& neighbor : it->second) {
            auto sub_result = dfs_postorder(graph, neighbor, visited);
            result.insert(result.end(), sub_result.begin(), sub_result.end());
        }
    }

    result.push_back(start);
    return result;
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

    auto path = dfs_recursive(graph, "A", "F");
    for (const auto& node : path) cout << node << " ";
    cout << endl;

    return 0;
}

