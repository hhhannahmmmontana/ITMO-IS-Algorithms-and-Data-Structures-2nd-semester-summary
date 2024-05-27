#include "base_includes.h"

std::vector<unsigned long> FindHamiltonianCycle(const std::vector<std::vector<bool>>& graph) {
    std::vector<unsigned long> q(graph.size());
    for (unsigned long i = 0; i < graph.size(); ++i) {
        q[i] = i;
    }
    for (unsigned long c = 0; c < graph.size() * (graph.size() - 1); ++c) {
        if (!graph[q[0]][q[1]]) {
            unsigned long i = 2;
            while (i < q.size() - 1 && (!graph[q[0]][q[i]] || !graph[q[1]][i + 1])) {
                ++i;
            }
            std::reverse(q.begin() + 1, q.begin() + i + 1);
        }
        q.push_back(q[0]);
        q.erase(q.begin());
    }
    return q;
}