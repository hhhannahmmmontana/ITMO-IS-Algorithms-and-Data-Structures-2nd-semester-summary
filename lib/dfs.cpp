#include "base_includes.h"

// realisation on adjacency list, unoriented graph
void DFS_Recursive(unsigned long id, const std::vector<std::vector<unsigned long>>& graph, std::vector<bool>& visited) {
    visited[id] = true;
    for (auto& i : graph[id]) {
        if (!visited[i]) {
            DFS_Recursive(i, graph, visited);
        }
    }
}

void DFS_Stack(const std::vector<std::vector<unsigned long>>& graph) {
    //std::vector T - graph node
    unsigned long start_id = 0;
    std::vector<bool> visited(graph.size(), false);
    while (start_id < graph.size()) {
        std::stack<unsigned long> s;
        s.push(start_id);
        while (!s.empty()) {
            auto current_node = s.top();
            s.pop();
            visited[current_node] = true;
            for (auto i : graph[current_node]) {
                if (!visited[i]) {
                    s.push(i);
                }
            }
        }

        while (start_id < graph.size() && visited[start_id]) {
            ++start_id;
        }
    }
}

