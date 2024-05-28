#include "base_includes.h"

void BridgeDfs(unsigned long id, unsigned long time, unsigned long prev, std::vector<unsigned long>& in, std::vector<unsigned long>& out,
               std::vector<std::vector<unsigned long>>& graph, std::vector<bool>& visited, std::vector<std::pair<unsigned long, unsigned long>>& ans) {
    in[id] = time;
    out[id] = time;
    ++time;
    for (auto i : graph[id]) {
        if (i == prev) {
            continue;
        }
        if (visited[i]) {
            out[id] = std::min(out[i], in[id]);
        } else {
            BridgeDfs(i, time, id, in, out, graph, visited, ans);
            out[id] = std::min(out[i], out[id]);
            if (in[id] < out[i]) {
                ans.emplace_back(id, i);
            }
        }
    }
}

void ArticulationPointsDfs(unsigned long id, unsigned long time, unsigned long prev, std::vector<unsigned long>& in, std::vector<unsigned long>& out,
               std::vector<std::vector<unsigned long>>& graph, std::vector<bool>& visited, std::vector<unsigned long>& ans) {
    unsigned long count = 0;
    in[id] = time;
    out[id] = time;
    ++time;
    for (auto i : graph[id]) {
        if (i == prev) {
            continue;
        }
        if (visited[i]) {
            out[id] = std::min(out[i], in[id]);
        } else {
            ArticulationPointsDfs(i, time, id, in, out, graph, visited, ans);
            ++count;
            out[id] = std::min(out[i], out[id]);
            if (prev != -1 && in[id] <= out[i]) {
                ans.push_back(id);
            }
        }
    }
    if (prev == -1 && count > 1) {
        ans.push_back(id);
    }
}