#include "base_includes.h"

void BFS(const std::vector<std::vector<unsigned long>>& graph) {
    //std::vector T - graph node
    unsigned long start_id = 0;
    std::vector<bool> visited(graph.size(), false);
    while (start_id < graph.size()) {
        std::queue<unsigned long> q;
        q.push(start_id);
        while (!q.empty()) {
            auto current_node = q.front();
            q.pop();
            visited[current_node] = true;
            for (auto i : graph[current_node]) {
                if (!visited[i]) {
                    q.push(i);
                }
            }
        }

        while (start_id < graph.size() && visited[start_id]) {
            ++start_id;
        }
    }
}