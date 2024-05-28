#include "base_includes.h"

void TPS(unsigned long id, const std::vector<std::vector<unsigned long>>& graph, std::vector<bool>& visited, std::stack<unsigned long>& ans) {
    visited[id] = true;
    for (auto i : graph[id]) {
        if (!visited[i]) {
            TPS(i, graph, visited, ans);
        }
    }
    ans.push(id);
}

std::vector<unsigned long> DAG(const std::vector<std::vector<unsigned long>>& graph, const std::vector<std::vector<unsigned long>>& weight) {
    std::vector<bool> visited(graph.size(), false);
    std::stack<unsigned long> tps;
    TPS(0, graph, visited, tps);
    std::vector<unsigned long> keys(graph.size(), ULONG_MAX);
    keys[tps.top()] = 0;
    while (!tps.empty()) {
        unsigned long id = tps.top();
        tps.pop();
        for (auto i : graph[id]) {
            if (keys[i] > keys[id] + weight[id][i]) {
                keys[i] = keys[id] + weight[id][i];
            }
        }
    }
    return keys;
}