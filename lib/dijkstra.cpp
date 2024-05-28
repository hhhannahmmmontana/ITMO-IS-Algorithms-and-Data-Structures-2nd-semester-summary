#include "base_includes.h"

// for dense graph
std::vector<unsigned long> DijkstraDense(unsigned long start, const std::vector<std::vector<unsigned long>>& graph, const std::vector<std::vector<unsigned long>>& weight) {
    std::vector<unsigned long> keys;
    for (auto& i : keys) {
        i = ULONG_MAX;
    }
    keys[start] = 0;
    std::vector<bool> used(graph.size(), false);
    for (unsigned long i = 0; i < graph.size(); ++i) {
        unsigned long v = ULONG_MAX;
        for (unsigned long u = 0; u < graph.size(); ++u) {
            if (!used[u] && (v == -1 || keys[u] < keys[v])) {
                v = u;
            }
        }
        if (v == ULONG_MAX) {
            break;
        }
        used[v] = true;
        for (auto& e : graph[v]) {
            if (keys[e] > keys[v] + weight[v][e]) {
                keys[e] = keys[v] + weight[v][e];
            }
        }
    }
    return keys;
}

// for sparse graph
std::vector<unsigned long> DijkstraSparse(unsigned long start, const std::vector<std::vector<unsigned long>>& graph, const std::vector<std::vector<unsigned long>>& weight) {
    // first - key, second - id
    std::set<std::pair<unsigned long, unsigned long>> q;
    std::vector<unsigned long> keys(graph.size(), ULONG_MAX);
    keys[start] = 0;
    q.emplace(keys[start], start);
    while (!q.empty()) {
        auto id = *q.begin();
        q.erase(id);
        for (auto i : graph[id.second]) {
            if (keys[i] > keys[id.second] + weight[id.second][i]) {
                q.erase({keys[i], i});
                keys[i] = keys[id.second] + weight[id.second][i];
                q.insert({keys[i], i});
            }
        }
    }
    return keys;
}