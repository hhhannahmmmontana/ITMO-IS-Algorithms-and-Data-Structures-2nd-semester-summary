#include "base_includes.h"



// pair - adjacent vertex, weight
std::vector<std::pair<unsigned long, unsigned long>> Prima(const std::vector<std::vector<std::pair<unsigned long, unsigned long>>>& graph) {
    // pair - priority, vertex id
    std::set<std::pair<unsigned long, unsigned long>> q;
    std::vector<unsigned long> keys(graph.size(), ULONG_MAX);
    std::vector<unsigned long> prev(graph.size(), ULONG_MAX);
    keys[0] = 0;
    q.emplace(keys[0], 0);
    while (!q.empty()) {
        unsigned long id = q.begin()->second;
        q.erase(q.begin());
        for (auto i : graph[id]) {
            unsigned long j = i.first, w = i.second;
            if (w < keys[j]) {
                q.erase({keys[j], j});
                keys[j] = w;
                prev[j] = i.second;
                q.insert({keys[j], j});
            }
        }
    }
    std::vector<std::pair<unsigned long, unsigned long>> ans;
    ans.reserve(graph.size());
    for (int i = 0; i < graph.size(); ++i) {
        ans.emplace_back(prev[i], i);
    }
    return ans;
}