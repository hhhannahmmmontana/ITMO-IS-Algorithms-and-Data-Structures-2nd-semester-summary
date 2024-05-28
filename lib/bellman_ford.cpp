#include "base_includes.h"

struct Edge {
    unsigned long a;
    unsigned long b;
    unsigned long w;
};

std::pair<std::vector<unsigned long>, std::vector<unsigned long>> BellmanFord(unsigned long V, const std::vector<Edge>& graph, unsigned long start) {
    std::vector<unsigned long> keys(V, ULONG_MAX);
    std::vector<unsigned long> prev(V, ULONG_MAX);
    keys[start] = 0;
    for (int i = 0; i < V - 1; ++i) {
        for (auto& e : graph) {
            if (keys[e.a] != ULONG_MAX && keys[e.b] > keys[e.a] + e.w) {
                keys[e.b] = keys[e.a] + e.w;
                prev[e.b] = e.a;
            }
        }
    }
    return {keys, prev};
}

std::vector<unsigned long> FindNegativeCycle(unsigned long V, const std::vector<Edge>& graph, unsigned long start) {
    auto bf_result = BellmanFord(V, graph, start);
    auto& keys = bf_result.first;
    auto& prev = bf_result.second;
    std::vector<unsigned long> negative_cycle;
    for (auto& e : graph) {
        // relaxation after V - 1 iteration == negative cycle
        if (keys[e.a] != ULONG_MAX && keys[e.b] > keys[e.a] + e.w) {
            unsigned long a = e.a;
            unsigned long b = e.b;
            // that's because we're not sure if the vertex is on the cycle, so we'll do it V times to be sure
            for (unsigned long i = 0; i < V; ++i) {
                b = prev[b];
            }
            a = b;
            // do-while because cycle has to contain at least one vertex
            do {
                negative_cycle.push_back(b);
                b = prev[b];
            } while (a != prev[b]);
            // we stored previous vertexes, so now we reverse the cycle
            std::reverse(negative_cycle.begin(), negative_cycle.end());
            break;
        }
    }
    return negative_cycle;
}