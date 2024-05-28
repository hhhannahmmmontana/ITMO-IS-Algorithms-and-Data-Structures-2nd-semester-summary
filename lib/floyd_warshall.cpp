#include "base_includes.h"

// realization = adjacency matrix
std::vector<std::vector<unsigned long>> FloydWarshall(std::vector<std::vector<unsigned long>> graph) {
    for (unsigned long i = 0; i < graph.size(); ++i) {
        for (unsigned long u = 0; u < graph.size(); ++u) {
            for (unsigned long v = 0; v < graph.size(); ++v) {
                // ULONG_MAX == infinity == no existing path
                if (graph[u][i] == ULONG_MAX || graph[i][v] == ULONG_MAX) {
                    continue;
                }
                if (graph[u][v] > graph[u][i] + graph[i][v]) {
                    graph[u][v] = graph[u][i] + graph[i][v];
                }
            }
        }
    }
    return graph;
}