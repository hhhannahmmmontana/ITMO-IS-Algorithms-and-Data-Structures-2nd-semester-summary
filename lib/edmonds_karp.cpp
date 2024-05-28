#include "base_includes.h"

bool BFS(unsigned long start, unsigned long end, const std::vector<std::vector<unsigned long>>& graph, const std::vector<std::vector<unsigned long>>& edges,
         std::vector<unsigned long>& parent) {
    std::vector<bool> visited(graph.size(), false);
    std::queue<unsigned long> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        unsigned long u = q.front();
        q.pop();
        for (auto v : graph[u]) {
            if (!visited[v] && edges[u][v] > 0) {
                parent[v] = u;
                if (v == end) {
                    return true;
                }
                q.push(v);
                visited[v] = true;
            }
        }
    }
    return false;
}

unsigned long EdmondsKarp(const std::vector<std::vector<unsigned long>>& graph, std::vector<std::vector<unsigned long>> edges, unsigned long start, unsigned long end) {
    std::vector<unsigned long> parent(graph.size(), ULONG_MAX);
    unsigned long ans = 0;
    while (BFS(start, end, graph, edges, parent)) {
        unsigned long u, v, delta = ULONG_MAX;
        for (v = end; v != start; v = parent[v]) {
            u = parent[v];
            delta = std::min(delta, edges[u][v]);
        }
        for (v = end; v != start; v = parent[v]) {
            u = parent[v];
            edges[u][v] -= delta;
            edges[v][u] += delta;
        }
        ans += delta;
    }
    return ans;
}