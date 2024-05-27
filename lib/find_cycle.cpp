#include "base_includes.h"

bool FindCycles(unsigned long id, const std::vector<std::vector<unsigned long>>& graph, std::vector<unsigned long>& prev, std::vector<uint8_t>& color, std::pair<unsigned long, unsigned long>& cycle) {
    color[id] = 1;
    for (auto& i : graph[id]) {
        if (color[i] == 0) {
            prev[i] = id;
            if (FindCycles(i, graph, prev, color, cycle)) {
                return true;
            }
        } else if (color[i] == 1) {
            cycle.first = id;
            cycle.second = i;
            return true;
        }
    }
    color[id] = 2;
    return false;
}

std::vector<unsigned long> GetCycle(const std::vector<std::vector<unsigned long>>& graph) {
    std::vector<uint8_t> color(graph.size(), 0);
    std::pair<unsigned long, unsigned long> cycle = {ULONG_MAX, ULONG_MAX};
    std::vector<unsigned long> prev(graph.size(), ULONG_MAX);
    //empty by default
    std::vector<unsigned long> ans;
    if (FindCycles(0, graph, prev, color, cycle)) {
        for (unsigned long v = cycle.first; v != cycle.second; v = prev[v]) {
            ans.push_back(cycle.first);
        }
        std::reverse(ans.begin(), ans.end());
    }
    return ans;
}