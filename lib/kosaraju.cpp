#include "base_includes.h"

void DFS_TPS(unsigned long id, const std::vector<std::vector<unsigned long>>& graph, std::vector<bool>& visited, std::stack<unsigned long>& ans) {
    visited[id] = true;
    for (auto& i : graph[id]) {
        if (!visited[i]) {
            DFS_TPS(i, graph, visited, ans);
        }
    }
    ans.push(id);
}

std::stack<unsigned long> PseudoTPS(const std::vector<std::vector<unsigned long>>& graph) {
    std::vector<bool> visited(graph.size(), false);
    std::stack<unsigned long> ans;
    for (unsigned long i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            DFS_TPS(i, graph, visited, ans);
        }
    }
    return ans;
}

void ReverseGraph_Recursive(unsigned long id, std::vector<std::vector<unsigned long>>& reversed_graph, const std::vector<std::vector<unsigned long>>& graph, std::vector<bool>& visited) {
    visited[id] = true;
    for (auto& i : graph[id]) {
        if (!visited[i]) {
            ReverseGraph_Recursive(i, reversed_graph, graph, visited);
            reversed_graph[i].push_back(id);
        }
    }
}

std::vector<std::vector<unsigned long>> ReverseGraph(const std::vector<std::vector<unsigned long>>& graph) {
    std::vector<std::vector<unsigned long>> ans(graph.size());
    std::vector<bool> visited(graph.size(), false);
    for (unsigned long i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            ReverseGraph_Recursive(i, ans, graph, visited);
        }
    }
    return ans;
}

void Kosaraju_DFS(unsigned long id, std::vector<unsigned long>& ans, const std::vector<std::vector<unsigned long>>& graph, std::vector<bool>& visited) {
    visited[id] = true;
    for (auto& i : graph[id]) {
        if (!visited[i]) {
            Kosaraju_DFS(i, ans, graph, visited);
        }
    }
    ans.push_back(id);
}

std::vector<std::vector<unsigned long>> Kosaraju(const std::vector<std::vector<unsigned long>>& graph) {
    auto tps_result = PseudoTPS(graph);
    std::vector<std::vector<unsigned long>> reversed_graph = ReverseGraph(graph);
    std::vector<bool> visited(graph.size(), false);
    std::vector<std::vector<unsigned long>> ans;
    while (!tps_result.empty()) {
        if (!visited[tps_result.top()]) {
            ans.emplace_back();
            Kosaraju_DFS(tps_result.top(), ans.back(), graph, visited);
        }
        tps_result.pop();
    }
    return ans;
}