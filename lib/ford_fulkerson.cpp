#include "base_includes.h"

bool DFS(unsigned long id, const std::vector<std::vector<unsigned long>>& graph, const std::vector<std::vector<unsigned long>>& edges, unsigned long end,
         std::vector<unsigned long>& parent, std::vector<bool>& visited) {
    visited[id] = true;
    for (auto i : graph[id]) {
        if (!visited[i] && edges[id][i] > 0) {
            parent[i] = id;
            if (i == end || DFS(i, graph, edges, end, parent, visited)) {
                return true;
            }
        }
    }
    return false;
}

unsigned long FordFulkerson(const std::vector<std::vector<unsigned long>>& graph, std::vector<std::vector<unsigned long>> edges, unsigned long start, unsigned long end) {
    std::vector<unsigned long> parent(graph.size(), ULONG_MAX);
    std::vector<bool> visited(graph.size(), false);
    unsigned long ans = 0;
    while (DFS(start, graph, edges, end, parent, visited)) {
        std::fill(visited.begin(), visited.end(), false);
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

// i took algo from neerc IDFK why it is literally kun
bool DFS_Pairs(unsigned long id, const std::vector<std::vector<unsigned long>>& left, std::vector<unsigned long>& ans, std::vector<bool>& visited) {
    visited[id] = true;
    for (auto i : left[id]) {
        if (ans[i] == ULONG_MAX || DFS_Pairs(i, left, ans, visited)) {
            ans[i] = id;
            return true;
        }
    }
    return false;
}

unsigned long FordFulkerson_Pairs(const std::vector<std::vector<unsigned long>>& left) {
    std::vector<unsigned long> ans(left.size(), ULONG_MAX);
    bool path_exists = true;
    while (path_exists) {
        path_exists = false;
        std::vector<bool> visited(left.size(), false);
        for (unsigned long i = 0; i < left.size(); ++i) {
            if (ans[i] == ULONG_MAX) {
                if (DFS_Pairs(i, left, ans, visited)) {
                    path_exists = true;
                }
            }
        }
    }
}