#include "base_includes.h"

void DFS(unsigned long id, const std::vector<std::vector<unsigned long>>& graph, std::vector<bool>& visited, std::stack<unsigned long>& ans) {
    visited[id] = true;
    for (auto& i : graph[id]) {
        if (!visited[i]) {
            DFS(i, graph, visited, ans);
        }
    }
    // THE WHOLE POINT!
    ans.push(id);
}
std::stack<unsigned long> TPS(std::vector<std::vector<unsigned long>>& graph) {
//  if(FindCycles(graph)) {
//      return {};
//  } - if has cycles -- tps impossible
    std::vector<bool> visited(graph.size(), false);
    std::stack<unsigned long> ans;
    for (unsigned long i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            DFS(i, graph, visited, ans);
        }
    }
    return ans;
}